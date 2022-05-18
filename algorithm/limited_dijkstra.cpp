#include "limited_dijkstra.h"

#include "graph/edge.h"
#include "graph/graph.h"

#include "util/util.h"

#include <queue>
#include <vector>

LimitedDijkstraAlgorithm::LimitedDijkstraAlgorithm(double distance_limit):
    distance_limit_(distance_limit) {}

Solution LimitedDijkstraAlgorithm::solve(const Graph &g, int source) {
  std::vector<bool> dijkstra_used(g.n());
  std::vector<Edge> dijkstra_result(g.n());
  {
    std::vector<double> dist(g.n(), std::numeric_limits<double>::max());
    std::priority_queue<std::pair<double, int>> q;

    dist[source] = 0;
    q.emplace(-dist[source], source);

    while (!q.empty()) {
      auto p = q.top();
      p.first = -p.first;

      if (p.first > distance_limit_) {
        break;
      }

      q.pop();

      if (dijkstra_used[p.second]) {
        continue;
      }
      dijkstra_used[p.second] = true;

      for (const auto &e: g.getEdges(p.second)) {
        if (!dijkstra_used[e.dst]) {
          if (dist[p.second] + e.length < dist[e.dst]) {
            dist[e.dst] = dist[p.second] + e.length;

            if (p.second == source) {
              dijkstra_result[e.dst] = e;
            } else {
              dijkstra_result[e.dst] = dijkstra_result[p.second];
            }

            q.emplace(-dist[e.dst], e.dst);
          }
        }
      }
    }
  }

  std::vector<Edge> result(g.n());
  {
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
  }

  for (int i = 0; i < g.n(); ++i) {
    if (dijkstra_used[i]) {
      result[i] = dijkstra_result[i];
    }
  }

  return Solution{.next_hop = std::move(result)};
}

std::string LimitedDijkstraAlgorithm::name() const {
  return "Limited Dijkstra (" + std::to_string(distance_limit_) + ") + BFS DAG DP";
}
