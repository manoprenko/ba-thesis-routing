#pragma once

#include "generator/distribution.h"

#include <random>
#include <vector>

class DiscreteDistribution : public Distribution {
public:
  explicit DiscreteDistribution(std::vector<std::pair<double, double>> weights);

  double gen() override;

private:
  std::vector<std::pair<double, double>> weights_;
  double sum_;
  std::uniform_real_distribution<double> distrib_;
};
