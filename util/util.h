#pragma once

#include <exception>
#include <iostream>

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

class Debug {
public:
  static void enable();

  static void disable();

  static bool isEnabled();

private:
  static bool enabled_;
};

#define DEBUG if (Debug::isEnabled())
