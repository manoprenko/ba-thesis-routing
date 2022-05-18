#pragma once

#include "generator.h"

#include "generator/distribution.h"

class RandomGraphGenerator final : public GraphGenerator {
public:
  RandomGraphGenerator(int n, int m, int seed = 0);

  [[nodiscard]] Graph generate(Distribution* distribution) const override;

private:
  int n_;
  int m_;

  int seed_;
};
