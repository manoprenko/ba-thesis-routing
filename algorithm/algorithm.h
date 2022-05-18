#pragma once

#include "algorithm/solution.h"

#include "graph/graph.h"

#include <string>

class Algorithm {
public:
  [[nodiscard]] virtual Solution solve(const Graph& g, int source) = 0;

  [[nodiscard]] virtual std::string name() const = 0;

  virtual ~Algorithm() = default;
};
