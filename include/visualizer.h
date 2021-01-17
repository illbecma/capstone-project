#if !defined(VISUALIZER_H)
#define VISUALIZER_H

#include <memory>

#include "network.h"

class Visualizer {
 public:
  Visualizer();
  void visualize();

 private:
  std::shared_ptr<Network> _net;
};

#endif  // VISUALIZER_H
