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

## Rubric points

- Loops, Functions, I/O
  - main.cpp#L50-L52 -> reading class file
  - main.cpp#L60-L71 -> looping through image paths
  - main.cpp#L33 -> function that draws predictions on the outputs 
- Object Oriented Programming
  - network.h -> class that encapsulates the functionality of a neural network detector
  - detector.h -> Base class for all the detector types
- Memory Management
  - main.cpp#L55-L56 -> smart pointer usage for Network class
  - network.cpp#L41 -> use of move function
  - network.cpp#L88 -> use of emplace_back function 
- Concurrency
  - main.cpp#L62-L82 -> running tasks for each of the images and running the draw function as soon as they are ready in the queue
  - network.cpp#L109-L115 L45-L46 -> usage of conditional variable to notify when an object enters and exits the queue
  - network.cpp#L36 -> usage of lock_guard when running detection