#if !defined(NETWORK_H)
#define NETWORK_H

#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <opencv2/dnn.hpp>
#include <queue>
#include <thread>

#include "detector.h"

typedef std::pair<cv::Mat, std::pair<std::vector<cv::Rect>, std::vector<int>>> BBoxPrediction;

class Network : public Detector {
 public:
  Network(std::string onnx);
  Network(std::string cfg, std::string weights);

  enum class NetworkType { Darknet, ONNX };
  static std::string to_string(NetworkType type);
  void setInputSize(const int height, const int width);
  const std::vector<cv::Rect>& getOutputBoxes() const { return _boxes; }

  void create(NetworkType type);
  void detect(const cv::Mat& input) override;
  void postProcess(const cv::Mat& input) override;
  BBoxPrediction getPrediction();

 private:
  void getOutputLayers();
  cv::dnn::Net _net;
  cv::Size _inputSize;
  std::string _cfg;
  std::string _weights;
  std::string _onnxFile;
  std::vector<std::string> _outputLayers;
  std::vector<cv::Mat> _outputs;
  std::vector<cv::Rect> _boxes;
  std::vector<int> _classIds;
  std::mutex _mutex;
  std::deque<BBoxPrediction> _predictions;
  std::condition_variable _cond;
};

#endif  // NETWORK_H