#include "fat_tree.h"

#include "graph/graph.h"
#include "graph/graph_builder.h"

FatTreeGenerator::FatTreeGenerator(int k, bool sym):
    k_(k),
    sym_(sym) {}

Graph FatTreeGenerator::generate(Distribution *distribution) const {
  const int k2 = k_ / 2;

  int core = k2 * k2;
  int aggr = k_ * k2;
  int edge = k_ * k2;
  int srv = k_ * k2 * k2;
  int n = core + aggr + edge + srv;

  GraphBuilder builder(n);

  // Core -- Aggregation
  for (int pod = 0; pod < k_; ++pod) {
    for (int agg_n = 0; agg_n < k2; ++agg_n) {
      int agg_id = core + pod * k2 + agg_n;
      for (int core_n = 0; core_n < k2; ++core_n) {
        int core_id = agg_n * k2 + core_n;

        if (sym_) {
          builder.addSymmetricEdge(agg_id, core_id, distribution->gen());
        } else {
          builder.addEdge(agg_id, core_id, distribution->gen());
          builder.addEdge(core_id, agg_id, distribution->gen());
        }
      }
    }
  }

  // Aggregation -- Edge
  for (int pod = 0; pod < k_; ++pod) {
    for (int agg_n = 0; agg_n < k2; ++agg_n) {
      for (int edge_n = 0; edge_n < k2; ++edge_n) {
        int agg_id = core + pod * k2 + agg_n;
        int edge_id = core + aggr + pod * k2 + edge_n;

        if (sym_) {
          builder.addSymmetricEdge(agg_id, edge_id, distribution->gen());
        } else {
          builder.addEdge(agg_id, edge_id, distribution->gen());
          builder.addEdge(edge_id, agg_id, distribution->gen());
        }
      }
    }
  }

  // Edge -- Servers
  for (int pod = 0; pod < k_; ++pod) {
    for (int edge_n = 0; edge_n < k2; ++edge_n) {
      int edge_id = core + aggr + pod * k2 + edge_n;
      for (int srv_n = 0; srv_n < k2; ++srv_n) {
        int srv_id = core + aggr + edge + pod * k2 * k2 + edge_n * k2 + srv_n;

        if (sym_) {
          builder.addSymmetricEdge(edge_id, srv_id, distribution->gen());
        } else {
          builder.addEdge(edge_id, srv_id, distribution->gen());
          builder.addEdge(srv_id, edge_id, distribution->gen());
        }
      }
    }
  }

  return builder.build();
}
