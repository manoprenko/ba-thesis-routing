#include "grid.h"

#include "graph/graph.h"
#include "graph/graph_builder.h"

#include <vector>

namespace {

static const std::vector<int> dx = {-1, 1, 0, 0};
static const std::vector<int> dy = {0, 0, -1, 1};

}

GridGenerator::GridGenerator(int n, bool sym):
    n_(n),
    sym_(sym) {}

Graph GridGenerator::generate(Distribution* distribution) const {
  GraphBuilder builder(n_ * n_);
  for (int i = 0; i < n_; ++i) {
    for (int j = 0; j < n_; ++j) {
      int u = i * n_ + j;
      for (int d = 0; d < 4; ++d) {
        int i1 = i + dx[d];
        int j1 = j + dy[d];
        if (0 <= i1 && i1 < n_ && 0 <= j1 && j1 < n_) {
          int v = i1 * n_ + j1;
          if (u < v) {
            if (sym_) {
              builder.addSymmetricEdge(u, v, distribution->gen());
            } else {
              builder.addEdge(u, v, distribution->gen());
              builder.addEdge(v, u, distribution->gen());
            }
          }
        }
      }
    }
  }
  return builder.build();
}
