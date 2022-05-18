#include "util.h"

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
