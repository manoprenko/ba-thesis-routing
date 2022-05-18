#include "util.h"

SimpleRng::SimpleRng(int L, int R, int seed)
    : rng_(seed), distribution_(L, R - 1) {}

int SimpleRng::operator()() {
  return distribution_(rng_);
}


bool Debug::enabled_ = false;

void Debug::enable() {
  enabled_ = true;
}

void Debug::disable() {
  enabled_ = false;
}

bool Debug::isEnabled() {
  return enabled_;
}
