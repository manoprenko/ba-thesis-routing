#pragma once

#include "algorithm/algorithm.h"
#include "algorithm/solution.h"

#include "graph/graph.h"

class PqDijkstraAlgorithm final : public Algorithm {
public:
  [[nodiscard]] Solution solve(const Graph &g, int source) override;

  [[nodiscard]] std::string name() const override;
};
