#pragma once

#include <vector>

struct Clustering {
  std::vector<int> cluster;
  std::vector<std::vector<int>> nodes_of_cluster;
};
