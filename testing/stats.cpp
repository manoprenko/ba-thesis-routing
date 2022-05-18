#include "stats.h"

#include <algorithm>

Stats calcStats(std::vector<double>& v) {
  std::sort(v.begin(), v.end());

  double sum = 0;
  for (double i : v) {
    sum += i;
  }

  return Stats{
    .min = v.front(),
    .max = v.back(),
    .avg = sum / v.size(),
    .mean = v[v.size() / 2],
    .p90 = v[v.size() * 90 / 100],
    .p95 = v[v.size() * 95 / 100],
  };
}

std::ostream& operator<<(std::ostream& stream, const Stats& s) {
  stream << "{ avg = " << s.avg
//      << "; min = " << s.min
      << ", mean = " << s.mean
//      << ", p90 = " << s.p90
//      << ", p95 = " << s.p95
//      << ", max = " << s.max
      << " }";
  return stream;
}
