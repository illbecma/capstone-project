#if !defined(DETECTOR_H)
#define DETECTOR_H

#include <opencv2/dnn.hpp>

class Detector {
 public:
  virtual void detect(){};
  virtual void postProcess(){};
  void setInput(cv::Mat* const image) { input = image; }
  void setConfThreshold(float conf) { confThreshold = conf; }
  void setNMSThreshold(float nms) { nmsThreshold = nms; }

 protected:
  cv::Mat* input;
  float confThreshold = 0.5; 
  float nmsThreshold = 0.4; 
};

#endif  // DETECTOR_H
