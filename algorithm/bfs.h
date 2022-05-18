#pragma once

#include "algorithm/algorithm.h"

class BfsAlgorithm final : public Algorithm {
public:
  [[nodiscard]] Solution solve(const Graph &g, int source) override;

  [[nodiscard]] std::string name() const override;
};
