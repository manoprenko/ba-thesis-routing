#include "random.h"

#include "graph/graph_builder.h"

#include "util/util.h"

RandomGraphGenerator::RandomGraphGenerator(int n, int m, int seed)
    : n_(n), m_(m), seed_(seed) {}

Graph RandomGraphGenerator::generate(Distribution* distribution) const {
  GraphBuilder builder(n_);
  SimpleRng edge_rng(0, n_, seed_);

  for (int i = 0; i < m_; ++i) {
    auto u = edge_rng();
    auto v = edge_rng();
    while (u == v) {
      v = edge_rng();
    }

    builder.addEdge(u, v, distribution->gen());
  }

  return builder.build();
}
