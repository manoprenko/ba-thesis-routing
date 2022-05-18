#pragma once

#include "generator.h"

#include "graph/graph.h"

#include "generator/distribution.h"

class DualHomedGenerator : public GraphGenerator {
public:
  DualHomedGenerator(int num_hosts, bool sym);

  [[nodiscard]] Graph generate(Distribution* distribution) const override;

private:
  int num_cores_ = 2;
  int num_hosts_;
  bool sym_;
};
