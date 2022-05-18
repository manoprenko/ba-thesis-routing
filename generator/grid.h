#pragma once

#include "generator.h"

#include "graph/graph.h"

#include "generator/distribution.h"

class GridGenerator : public GraphGenerator {
public:
  GridGenerator(int n, bool sym);

  [[nodiscard]] Graph generate(Distribution* distribution) const override;

private:
  int n_;
  bool sym_;
};
