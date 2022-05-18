#include "bfs.h"

#include "graph/edge.h"
#include "graph/graph.h"

#include "algorithm/solution.h"

#include <vector>
#include <queue>

Solution BfsAlgorithm::solve(const Graph &g, int source) {
  std::vector<Edge> result(g.n());
  std::vector<bool> used(g.n());
  std::queue<int> q;

  result[source] = Edge{};
  q.push(source);
  used[source] = true;

  while (!q.empty()) {
    auto u = q.front();
    q.pop();

    for (const auto& e : g.getEdges(u)) {
      if (!used[e.dst]) {
        used[e.dst] = true;
        if (u == source) {
          result[e.dst] = e;
        } else {
          result[e.dst] = result[u];
        }
        q.push(e.dst);
      }
    }
  }

  return Solution{.next_hop = std::move(result)};
}

std::string BfsAlgorithm::name() const {
  return "BFS";
}
