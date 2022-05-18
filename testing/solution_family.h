#pragma once

#include "algorithm/algorithm.h"
#include "algorithm/solution.h"

#include "graph/graph.h"

#include <vector>

struct SolutionFamily {
  std::vector<Solution> from;
};

SolutionFamily solveAll(const Graph& g, Algorithm* algo);
