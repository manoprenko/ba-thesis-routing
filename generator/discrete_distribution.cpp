#include "discrete_distribution.h"

#include "util/util.h"

namespace {

double sum(const std::vector<std::pair<double, double>>& weights) {
  double s = 0;
  for (const auto& p : weights) {
    s += p.second;
  }
  return s;
}

}

DiscreteDistribution::DiscreteDistribution(std::vector<std::pair<double, double>> weights):
    weights_(std::move(weights)),
    sum_(sum(weights_)),
    distrib_(0, sum_) {}

double DiscreteDistribution::gen() {
  double x = distrib_(rng_);
  for (const auto& p : weights_) {
    if (x <= p.second) {
      return p.first;
    } else {
      x -= p.second;
    }
  }
  ASSERT(false, "Invalid discrete generation, sum = " << sum_ << ", x = " << x);
}
