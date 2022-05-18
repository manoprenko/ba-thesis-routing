#pragma once

#include <exception>
#include <iostream>
#include <random>

struct AssertionError : public std::exception {
};

#define ASSERT(expr, message)                         \
  do {                                                \
    if (!(expr)) {                                    \
      std::cerr << "Assertion failed\n";              \
      std::cerr << message << "\n";                   \
      std::cerr << "Expression:\t" << #expr << "\n";  \
      throw AssertionError{};                         \
    }                                                 \
  } while (false)


class SimpleRng {
  // Generates uniformly distributed numbers on semi-interval [L, R)
public:
  SimpleRng(int L, int R, int seed = 0);

  int operator()();

private:
  std::mt19937_64 rng_;
  std::uniform_int_distribution<int> distribution_;
};


class Debug {
public:
  static void enable();

  static void disable();

  static bool isEnabled();

private:
  static bool enabled_;
};

#define DEBUG if (Debug::isEnabled())

