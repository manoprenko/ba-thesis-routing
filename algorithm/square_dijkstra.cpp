#include "square_dijkstra.h"

#include "algorithm/solution.h"

#include "graph/edge.h"
#include "graph/graph.h"

#include <vector>

Solution SquareDijkstraAlgorithm::solve(const Graph &g, int source) {
  std::vector<double> dist(g.n(), std::numeric_limits<double>::max());
  std::vector<bool> used(g.n());

  std::vector<Edge> result(g.n());
  result[source] = Edge{};

  dist[source] = 0;
  for (int i = 0; i < g.n(); ++i) {
    int best = -1;
    for (int j = 0; j < g.n(); ++j) {
      if (!used[j] && (best == -1 || dist[j] < dist[best])) {
        best = j;
      }
    }

    if (best == -1) {
      // TODO: Assert here?
      break;
    }

    used[best] = true;
    for (const auto& e : g.getEdges(best)) {
      if (dist[best] + e.length < dist[e.dst]) {
        dist[e.dst] = dist[best] + e.length;

        if (best == source) {
          result[e.dst] = e;
        } else {
          result[e.dst] = result[best];
        }
      }
    }
  }

  return Solution{.next_hop = std::move(result)};
}

std::string SquareDijkstraAlgorithm::name() const {
  return "Dijkstra (n^2)";
}
