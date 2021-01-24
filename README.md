# CPPND: Capstone - Object Detection with YOLOv3 Darknet model using OpenCV

This is the code for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project runs object detection inference of a directory of image files using a pretrained Darknet YOLO neural network using OpenCV library. The code visualizes and stores the results using a multi-theaded approach. Can be further extended to other types of Neural Networks and different type of input data.

Make sure to download the YOLOv3 weight file before running: “https://pjreddie.com/media/files/yolov3.weights”

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* opencv >= 4.2.0
  * Linux: [Official site](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)
  * Windows:[Official site](https://docs.opencv.org/master/d3/d52/tutorial_windows_install.html)

## Basic Build Instructions

1. Clone this repo.
2. run `make build` from the source
3. Go to Build dir: `cd build`
4. Run it: `./capstone`.

## No Binary COPY Build Instructions

1. Clone this repo.
2. run `make build-no-copy` from the source
3. Go to Build dir: `cd build`
4. Run it: `./capstone`.

> Make sure to correct the paths to image dir and binaries in the code.