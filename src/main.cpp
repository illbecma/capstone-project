#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "network.h"

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
void drawPred(Mat& frame, std::vector<cv::Rect> bboxes, int& img_count) {
  // Draw a rectangle displaying the bounding box
  for (auto bbox : bboxes) {
    rectangle(frame, bbox, Scalar(255, 255, 255), 1);
  }
  std::string img_name = "out_image_" + std::to_string(img_count) + ".jpg";
  std::cout << "Writing image: " << img_name << std::endl;
  cv::imwrite(img_name, frame);
  ++img_count;
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
  std::shared_ptr nn =
      std::make_shared<Network>(modelConfiguration, modelWeights);
  nn->setInputSize(inpHeight, inpWidth);
  nn->setConfThreshold(confThreshold);
  nn->setNMSThreshold(nmsThreshold);

  std::string dir_path = "images";
  std::vector<std::string> image_paths;
  for (const auto& entry : std::filesystem::directory_iterator(dir_path))
    image_paths.push_back(entry.path());

  std::vector<std::future<void>> futures;

  for (auto imgp : image_paths) {
    // Runs the forward pass to get output of the output layers
    // Runs post-processing to keep only a few high-score boxes
    futures.emplace_back(
        std::async(std::launch::async, &Network::detect, nn, imread(imgp)));
  }
  int img_cnt = 0;
  while (true) {
    auto prediction = nn->getPrediction();
    drawPred(prediction.first, prediction.second, img_cnt);
  }

  std::for_each(futures.begin(), futures.end(),
                [](std::future<void>& ftr) { ftr.wait(); });

  return 0;
}
