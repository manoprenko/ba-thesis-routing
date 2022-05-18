#pragma once

#include "graph/graph.h"

#include <vector>

class GraphBuilder {
  friend class Graph;

public:
  explicit GraphBuilder(int n);

  void addEdge(int from, int to, double length);

  void addSymmetricEdge(int v1, int v2, double length);

  [[nodiscard]] Graph build() const;

private:
  const int n_;

  int indexer_ = 0;
  std::vector<Edge> edge_list_;
};
