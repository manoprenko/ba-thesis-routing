#include "pq_dijkstra.h"

#include "algorithm/solution.h"

#include <vector>
#include <queue>

Solution PqDijkstraAlgorithm::solve(const Graph &g, int source) {
  std::vector<double> dist(g.n(), std::numeric_limits<double>::max());
  std::vector<bool> used(g.n());
  std::vector<Edge> result(g.n());
  std::priority_queue<std::pair<double, int>> q;

  dist[source] = 0;
  q.emplace(-dist[source], source);

  while (!q.empty()) {
    auto p = q.top();
    p.first = -p.first;
    q.pop();

    if (used[p.second]) {
      continue;
    }
    used[p.second] = true;

    for (const auto& e : g.getEdges(p.second)) {
      if (!used[e.dst]) {
        if (dist[p.second] + e.length < dist[e.dst]) {
          dist[e.dst] = dist[p.second] + e.length;

          if (p.second == source) {
            result[e.dst] = e;
          } else {
            result[e.dst] = result[p.second];
          }

          q.emplace(-dist[e.dst], e.dst);
        }
      }
    }
  }

  return Solution{.next_hop = std::move(result)};
}

std::string PqDijkstraAlgorithm::name() const {
  return "Dijkstra (std::priority_queue)";
}
