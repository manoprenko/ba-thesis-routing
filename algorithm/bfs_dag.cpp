#include "bfs_dag.h"

#include "graph/graph.h"
#include "algorithm/solution.h"

#include <vector>

Solution BfsDagAlgorithm::solve(const Graph &g, int source) {
  std::vector<int> bfs_dist(g.n(), -1);
  std::vector<int> bfs_order;
  bfs_order.reserve(g.n());
  int q_ptr = 0;

  bfs_order.push_back(source);
  bfs_dist[source] = 0;

  while (q_ptr < bfs_order.size()) {
    int u = bfs_order[q_ptr];
    ++q_ptr;

    for (const auto& e : g.getEdges(u)) {
      if (bfs_dist[e.dst] == -1) {
        bfs_dist[e.dst] = bfs_dist[u] + 1;
        bfs_order.push_back(e.dst);
      }
    }
  }

  std::vector<Edge> result(g.n());
  std::vector<double> dist(g.n(), std::numeric_limits<double>::max());
  dist[source] = 0;
  for (int u : bfs_order) {
    for (const auto& e : g.getEdges(u)) {
      if (dist[e.dst] > dist[u] + e.length) {
        dist[e.dst] = dist[u] + e.length;
        if (u == source) {
          result[e.dst] = e;
        } else {
          result[e.dst] = result[u];
        }
      }
    }
  }

  return Solution{.next_hop = std::move(result)};
}

std::string BfsDagAlgorithm::name() const {
  return "BFS DAG based DP";
}
