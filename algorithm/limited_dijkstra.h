#pragma once

#include "algorithm/algorithm.h"
#include "algorithm/solution.h"

#include "graph/graph.h"

class LimitedDijkstraAlgorithm final : public Algorithm {
public:
  explicit LimitedDijkstraAlgorithm(double distance_limit);

  [[nodiscard]] Solution solve(const Graph &g, int source) override;

  [[nodiscard]] std::string name() const override;

private:
  double distance_limit_;
};
