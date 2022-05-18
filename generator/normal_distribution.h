#pragma once

#include "distribution.h"

#include <random>

class NormalDistribution : public Distribution {
public:
  NormalDistribution(double mean, double variance);

  double gen() override;

private:
  std::normal_distribution<double> distrib_;
};
