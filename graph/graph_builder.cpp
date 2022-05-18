#include "graph_builder.h"

#include "graph/graph.h"

#include "util/util.h"

GraphBuilder::GraphBuilder(int n) : n_(n), indexer_(0) {}

void GraphBuilder::addEdge(int from, int to, double length) {
  ASSERT(0 <= from && from < n_, "Invalid vertex index " << from << " for graph size " << n_);
  ASSERT(0 <= to && to < n_, "Invalid vertex index " << to << " for graph size " << n_);

  edge_list_.push_back(Edge{
      .id = indexer_++,
      .src = from,
      .dst = to,
      .length = length,
  });
}

void GraphBuilder::addSymmetricEdge(int v1, int v2, double length) {
  addEdge(v1, v2, length);
  addEdge(v2, v1, length);
}

Graph GraphBuilder::build() const {
  return Graph(*this);
}
