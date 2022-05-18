#include "validator.h"

#include "graph/graph.h"

#include "testing/solution_family.h"

#include "util/util.h"

#include <iostream>
#include <chrono>
#include <vector>

bool dfs(
    const Graph& g,
    const SolutionFamily& go,
    int dest,
    std::vector<std::vector<double>>& dist,
    std::vector<int>& used,
    std::vector<int>& stack,
    int u
) {
  // returns true if loop has been detected

  used[u] = 1;
  stack.push_back(u);

  if (u == dest) {
    dist[u][dest] = 0;
  } else {
    const auto& e = go.from[u].next_hop[dest];
    if (used[e.dst] == 1) {
      // Loop detected
      DEBUG {
        std::vector<int> loop;
        while (stack.back() != e.dst) {
          loop.push_back(stack.back());
          stack.pop_back();
        }
        loop.push_back(stack.back());
        std::reverse(loop.begin(), loop.end());

        std::cout << "Loop detected" << std::endl;
        std::cout << "Dest: " << dest << std::endl;
        std::cout << "Loop size: " << loop.size() << std::endl;
        std::cout << "Loop:";
        for (int x: loop) {
          std::cout << " " << x;
        }
        std::cout << std::endl;
      }
      return true;
    } else if (used[e.dst] == 0) {
      if (dfs(g, go, dest, dist, used, stack, e.dst)) {
        return true;
      }
    }
    dist[u][dest] = dist[e.dst][dest] + e.length;
  }

  stack.pop_back();
  used[u] = 2;
  return false;
}

std::vector<std::vector<double>> getDistancesFast(const Graph& g, const SolutionFamily& go) {
  std::vector<std::vector<double>> dist(g.n(), std::vector<double>(g.n()));

  for (int dest = 0; dest < g.n(); ++dest) {
    std::vector<int> used(g.n());
    for (int i = 0; i < g.n(); ++i) {
      if (!used[i]) {
        std::vector<int> stack;
        if (dfs(g, go, dest, dist, used, stack, i)) {
          return {};
        }
      }
    }
  }

  return dist;
}

//std::vector<std::vector<double>> getDistances(const Graph& g, const SolutionFamily& go) {
//  std::vector<std::vector<double>> dist(g.n(), std::vector<double>(g.n()));
//
//  for (int s = 0; s < g.n(); ++s) {
//    for (int t = 0; t < g.n(); ++t) {
//      double len = 0;
//      int cur = s;
//      int hops = 0;
//
//      while (cur != t) {
//        const auto& e = go.from[cur].next_hop[t];
//        len += e.length;
//        cur = e.dst;
//        ++hops;
//
//        if (hops > g.n()) {
//          // Loop
//          return {};
//        }
//      }
//
//      dist[s][t] = len;
//    }
//  }
//
//  return dist;
//}

Result validateSolution(const Graph& g, const SolutionFamily& solution, const SolutionFamily& best) {
//  auto debugDist = getDistances(g, solution);
  auto dist = getDistancesFast(g, solution);

  if (dist.empty()) {
    return Result::invalid();
  }

//  for (int i = 0; i < g.n(); ++i) {
//    for (int j = 0; j < g.n(); ++j) {
//      ASSERT(abs(dist[i][j] - debugDist[i][j]) < 1e-5, "i = " << i << ", j = " << j << ", dist = " << dist[i][j] << ", dbg = " << debugDist[i][j]);
//    }
//  }

  auto best_dist = getDistancesFast(g, best);

  if (best_dist.empty()) {
    return Result::invalid();
  }

  std::vector<double> elongs;
  for (int s = 0; s < g.n(); ++s) {
    for (int t = 0; t < g.n(); ++t) {
      if (s == t) {
        continue;
      }
      if (best_dist[s][t] != 0) {
        double elongation = static_cast<double>(dist[s][t] - best_dist[s][t]) / best_dist[s][t];
        elongs.push_back(elongation * 100);
      }
    }
  }

  return Result{
      .is_valid = true,
      .stats = calcStats(elongs),
  };
}

Result validateAlgo(const Graph& g, Algorithm* algo, Algorithm* best) {
  auto algo_sol = solveAll(g, algo);
  auto best_sol = solveAll(g, best);

  std::cout << "Validating..." << std::endl;
  return validateSolution(g, algo_sol, best_sol);
}

void evaluateAlgo(
    GraphGenerator* generator,
    Distribution* distrib,
    Algorithm* algo,
    Algorithm* best
) {
  auto graph = generator->generate(distrib);
  std::cout << "n = " << graph.n() << std::endl;
  DEBUG {
    std::cout << graph.graphViz() << std::endl;
  };
  auto result = validateAlgo(graph, algo, best);
  std::cout << "Evaluation result: " << result << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Result& res) {
  if (!res.is_valid) {
    stream << "<INVALID>";
  } else {
    stream << res.stats;
  }
  return stream;
}

Result Result::invalid() {
  return Result{
      .is_valid = false,
      .stats = {},
  };
}
