#pragma once

#include <vector>
#include <string>
#include <iostream>

struct Stats {
  double min;
  double max;
  double avg;
  double mean;
  double p90;
  double p95;
};

Stats calcStats(std::vector<double>& v);

std::ostream& operator<<(std::ostream& stream, const Stats& s);
