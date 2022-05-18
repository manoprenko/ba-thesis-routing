#include "dual_homed.h"

#include "graph/graph.h"
#include "graph/graph_builder.h"

DualHomedGenerator::DualHomedGenerator(int num_hosts, bool sym):
    num_hosts_(num_hosts),
    sym_(sym) {
}

Graph DualHomedGenerator::generate(Distribution *distribution) const {
  GraphBuilder builder(num_cores_ + num_hosts_);
  for (int i = 0; i < num_cores_; ++i) {
    for (int j = 0; j < num_hosts_; ++j) {
      if (sym_) {
        builder.addSymmetricEdge(i, num_cores_ + j, distribution->gen());
      } else {
        builder.addEdge(i, num_cores_ + j, distribution->gen());
        builder.addEdge(num_cores_ + j, i, distribution->gen());
      }
    }
  }
  return builder.build();
}
