// This code is based on LearnOpenCV code writtend at BigVision LLC. It is based
// on the OpenCV project. It is subject to the license terms in the LICENSE file
// found in this distribution and at http://opencv.org/license.html

// Usage example:  ./DeepLearning_ch12 image.jpg
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include "Network.h"

using namespace cv;
using namespace dnn;
using namespace std;

// Initialize the parameters
float confThreshold = 0.5;  // Confidence threshold
float nmsThreshold = 0.4;   // Non-maximum suppression threshold
int inpWidth = 416;         // Width of network's input image
int inpHeight = 416;        // Height of network's input image
vector<string> classes;

// Draw the predicted bounding box
void drawPred(int classId, float conf, int left, int top, int right, int bottom,
              Mat& frame) {
  // Draw a rectangle displaying the bounding box
  rectangle(frame, Point(left, top), Point(right, bottom),
            Scalar(255, 255, 255), 1);

  // Get the label for the class name and its confidence
  string conf_label = format("%.2f", conf);
  string label = "";
  if (!classes.empty()) {
    label = classes[classId] + ":" + conf_label;
  }

  // Display the label at the top of the bounding box
  int baseLine;
  Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
  top = max(top, labelSize.height);
  rectangle(frame, Point(left, top - labelSize.height),
            Point(left + labelSize.width, top + baseLine),
            Scalar(255, 255, 255), FILLED);
  putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.5,
          Scalar(0, 0, 0), 1, LINE_AA);
}

// Remove the bounding boxes with low confidence using non-maxima suppression
void postprocess(Mat* frame, const vector<Mat>& outs) {

}

int main(int argc, char** argv) {
  // Load names of classes
  string classesFile = "coco.names";
  ifstream ifs(classesFile.c_str());
  string line;
  while (getline(ifs, line)) classes.push_back(line);

  // Give the configuration and weight files for the model
  String modelConfiguration = "yolov3.cfg";
  String modelWeights = "yolov3.weights";

  // Load the network
  Network nn(modelConfiguration, modelWeights);

  std::shared_ptr<cv::Mat> input;

  input = std::make_shared<cv::Mat>(imread("images/dog.jpg"));

  // Stop the program if reached end of video
  if (input->empty()) {
    cout << "No input image" << endl;
    return 0;
  }

  nn.setInputSize(inpHeight, inpWidth);
  nn.setConfThreshold(confThreshold);
  nn.setNMSThreshold(nmsThreshold);
  nn.setInput(input.get());

  // Runs the forward pass to get output of the output layers
  // Runs post-processing to keep only a few high-score boxes
  nn.detect();

  // cv::drawPred(classIds[idx], confidences[idx], box.x, box.y, box.x + box.width,
    //         box.y + box.height, *frame);

  namedWindow("Results");
  imshow("Results", *input);
  waitKey(0);

  return 0;
}
