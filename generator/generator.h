#pragma once

#include "generator/distribution.h"

#include "graph/graph.h"

class GraphGenerator {
public:
  [[nodiscard]] virtual Graph generate(Distribution* distribution) const = 0;

  virtual ~GraphGenerator() = default;
};
