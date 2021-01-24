#if !defined(DETECTOR_H)
#define DETECTOR_H

#include <opencv2/dnn.hpp>

class Detector {
 public:
  virtual void detect(const cv::Mat& input){};
  virtual void postProcess(const cv::Mat& input){};
  void setConfThreshold(float conf) { confThreshold = conf; }
  void setNMSThreshold(float nms) { nmsThreshold = nms; }

 protected:
  float confThreshold = 0.5; 
  float nmsThreshold = 0.4; 
};

#endif  // DETECTOR_H
