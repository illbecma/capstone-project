#if !defined(NETWORK_H)
#define NETWORK_H

#include <iostream>
#include <memory>
#include <opencv2/dnn.hpp>

#include "detector.h"

class Network : public Detector {
 public:
  Network(std::string onnx);
  Network(std::string cfg, std::string weights);

  enum class NetworkType { Darknet, ONNX };
  static std::string to_string(NetworkType type);
  void setInputSize(const int height, const int width);
  const std::vector<cv::Rect>& getOutputBoxes() const { return _boxes; }

  void create(NetworkType type);
  void detect() override;
  void postProcess() override;

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
};

#endif  // NETWORK_H