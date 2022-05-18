#pragma once

#include "generator.h"

#include "graph/graph.h"

#include "generator/distribution.h"

class FatTreeGenerator : public GraphGenerator {
public:
  FatTreeGenerator(int k, bool sym);

  [[nodiscard]] Graph generate(Distribution* distribution) const override;

private:
  int k_;
  bool sym_;
};
