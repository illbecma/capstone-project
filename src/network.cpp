#include "network.h"

Network::Network(std::string cfg, std::string weights)
    : _cfg(cfg), _weights(weights) {
  try {
    create(NetworkType::Darknet);
  } catch (...) {
    std::cerr << "Initialization of Darknet model failed." << std::endl;
  }
}

std::string Network::to_string(NetworkType type) {
  switch (type) {
    case (NetworkType::Darknet):
      return "Darknet";
      break;
    default:
      return "";
      break;
  }
}

void Network::create(NetworkType type) {
  if (type == NetworkType::Darknet) {
    _net = cv::dnn::readNetFromDarknet(_cfg, _weights);
    getOutputLayers();
  } else {
    throw std::invalid_argument("Type " + Network::to_string(type) +
                                "is not supported!");
  }
  _net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
  _net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

void Network::detect(const cv::Mat& input) {
  std::lock_guard<std::mutex> lck(_mutex);
  // Create a 4D blob from a frame.
  cv::Mat blob = cv::dnn::blobFromImage(input, 1 / 255.0, _inputSize,
                                        cv::Scalar(0, 0, 0), true, false);
  // Run forward step on the blob.
  _net.setInput(std::move(blob));
  _net.forward(_outputs, _outputLayers);
  postProcess(input);
  // add prediction to queue and notify
  _predictions.push_back(std::make_pair(input, std::make_pair(_boxes, _classIds)));
  _cond.notify_one();
}

void Network::postProcess(const cv::Mat& input) {
  std::vector<int> classIds;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;

  for (size_t i = 0; i < _outputs.size(); ++i) {
    // Scan through all the bounding boxes output from the network and keep only
    // the ones with high confidence scores. Assign the box's class label as the
    // class with the highest score for the box.
    float* data = (float*)_outputs[i].data;
    for (int j = 0; j < _outputs[i].rows; ++j, data += _outputs[i].cols) {
      cv::Mat scores = _outputs[i].row(j).colRange(5, _outputs[i].cols);
      cv::Point classIdPoint;
      double confidence;
      // Get the value and location of the maximum score
      minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
      if (confidence > confThreshold) {
        int centerX = (int)(data[0] * input.cols);
        int centerY = (int)(data[1] * input.rows);
        int width = (int)(data[2] * input.cols);
        int height = (int)(data[3] * input.rows);
        int left = centerX - width / 2;
        int top = centerY - height / 2;

        classIds.push_back(classIdPoint.x);
        confidences.push_back((float)confidence);
        boxes.push_back(cv::Rect(left, top, width, height));
      }
    }
  }

  // Perform non maximum suppression to eliminate redundant overlapping boxes
  // with lower confidences.
  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
  _boxes.clear();
  _classIds.clear();
  for (size_t i = 0; i < indices.size(); ++i) {
    int idx = indices[i];
    _boxes.emplace_back(boxes[idx]);
    _classIds.emplace_back(classIds[idx]);
  }
}

void Network::getOutputLayers() {
  if (_outputLayers.empty()) {
    auto outLayers = _net.getUnconnectedOutLayers();
    auto layersNames = _net.getLayerNames();

    _outputLayers.resize(outLayers.size());
    for (size_t i = 0; i < outLayers.size(); ++i) {
      _outputLayers[i] = layersNames[outLayers[i] - 1];
    }
  }
}

void Network::setInputSize(const int height, const int width) {
  _inputSize = cv::Size(height, width);
}

BBoxPrediction Network::getPrediction() {
  std::unique_lock<std::mutex> uLock(_mutex);
  _cond.wait(uLock, [this] { return !_predictions.empty(); });
  BBoxPrediction p = std::move(_predictions.back());
  _predictions.pop_back();
  return p;
}