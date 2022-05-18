#pragma once

#include "algorithm/algorithm.h"

#include "graph/graph.h"

#include "generator/distribution.h"
#include "generator/generator.h"

#include "testing/solution_family.h"
#include "testing/stats.h"

#include <iostream>
#include <vector>

struct Result {
  static Result invalid();

  bool is_valid;

  Stats stats;
};

std::vector<std::vector<double>> getDistancesFast(const Graph& g, const SolutionFamily& go);

Result validateSolution(const Graph& g, const SolutionFamily& solution, const SolutionFamily& best);
Result validateAlgo(const Graph& g, Algorithm* algo, Algorithm* best);
void evaluateAlgo(
    GraphGenerator* generator,
    Distribution* distrib,
    Algorithm* algo,
    Algorithm* best
);

std::ostream& operator<<(std::ostream& stream, const Result& res);
