#pragma once

#include <cstdint>
#include <random>

class Distribution {
public:
  explicit Distribution(uint64_t seed = 0);

  virtual double gen() = 0;

  virtual ~Distribution() = default;

protected:
  std::mt19937_64 rng_;
};
