#include "set_dijkstra.h"

#include "graph/graph.h"

#include "algorithm/solution.h"

#include <set>
#include <vector>

Solution SetDijkstraAlgorithm::solve(const Graph &g, int source) {
  std::vector<double> dist(g.n(), std::numeric_limits<double>::max());
  std::vector<bool> used(g.n());
  std::vector<Edge> result(g.n());
  std::set<std::pair<double, int>> q;

  dist[source] = 0;
  q.emplace(dist[source], source);

  while (!q.empty()) {
    auto p = q.extract(q.begin()).value();
    used[p.second] = true;
    for (const auto& e : g.getEdges(p.second)) {
      if (!used[e.dst]) {
        if (dist[p.second] + e.length < dist[e.dst]) {
          q.erase({dist[e.dst], e.dst});
          dist[e.dst] = dist[p.second] + e.length;

          if (p.second == source) {
            result[e.dst] = e;
          } else {
            result[e.dst] = result[p.second];
          }

          q.insert({dist[e.dst], e.dst});
        }
      }
    }
  }

  return Solution{.next_hop = std::move(result)};
}

std::string SetDijkstraAlgorithm::name() const {
  return "Dijkstra (std::set)";
}
