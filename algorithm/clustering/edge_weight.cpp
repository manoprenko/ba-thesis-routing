#include "edge_weight.h"

#include "graph/graph.h"
#include "graph/edge.h"

#include "algorithm/clustering/clustering.h"
#include "algorithm/clustering/dsu.h"

#include <algorithm>

Clustering clusterByEdgeWeights(const Graph& g, int size_limit) {
  std::vector<Edge> edges;
  for (int i = 0; i < g.n(); ++i) {
    for (const auto& e : g.getEdges(i)) {
      edges.push_back(e);
    }
  }
  std::sort(edges.begin(), edges.end(), [](const auto& lhs, const auto& rhs) {
    if (lhs.length != rhs.length) {
      return lhs.length < rhs.length;
    }
    return lhs.id < rhs.id;
  });

  DSU dsu(g.n());
  for (const auto& e : edges) {
    if (dsu.get(e.src) != dsu.get(e.dst)) {
      if (dsu.setSize(e.src) + dsu.setSize(e.dst) <= size_limit) {
        dsu.unite(e.src, e.dst);
      }
    }
  }

  std::vector<std::vector<int>> clusters(dsu.setCount());
  std::vector<int> cl_num(g.n(), -1);
  int last = 0;
  for (int i = 0; i < g.n(); ++i) {
    int cl = dsu.get(i);
    if (cl_num[cl] == -1) {
      cl_num[cl] = last++;
    }
    clusters[cl_num[cl]].push_back(i);
  }

  std::vector<int> cluster(g.n());
  for (int i = 0; i < last; ++i) {
    for (int j : clusters[i]) {
      cluster[j] = i;
    }
  }

  return Clustering{ .cluster = std::move(cluster), .nodes_of_cluster = std::move(clusters) };
}
