#include "normal_distribution.h"

NormalDistribution::NormalDistribution(double mean, double variance):
    distrib_(mean, variance) {}

double NormalDistribution::gen() {
  return std::max(0.0, distrib_(rng_));
}
