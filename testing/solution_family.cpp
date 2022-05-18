#include "solution_family.h"

#include "algorithm/algorithm.h"

#include "graph/graph.h"

#include <chrono>
#include <iostream>

SolutionFamily solveAll(const Graph& g, Algorithm* algo) {
  SolutionFamily result;
  std::cout << "Running algorithm: " << algo->name() << std::endl;

  auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < g.n(); ++i) {
    result.from.push_back(algo->solve(g, i));
  }
  auto finish = std::chrono::steady_clock::now();

  auto run_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
  double rt_seconds = static_cast<double>(run_time) / 1e9;
  std::cout << "Algorithm `" << algo->name() << "` run time: " << rt_seconds << " s" << std::endl;

  return result;
}
