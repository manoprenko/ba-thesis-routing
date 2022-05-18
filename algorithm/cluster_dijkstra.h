#pragma once

#include "algorithm/algorithm.h"
#include "algorithm/solution.h"

#include "graph/graph.h"

class ClusteredDijkstraAlgorithm final : public Algorithm {
public:
  explicit ClusteredDijkstraAlgorithm(int cluster_size_limit);

  [[nodiscard]] Solution solve(const Graph &g, int source) override;

  [[nodiscard]] std::string name() const override;

private:
  int cluster_size_limit_;
};
