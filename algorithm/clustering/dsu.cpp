#include "dsu.h"

DSU::DSU(int n):
    par_(n),
    size_(n),
    set_cnt_(n) {
  for (int i = 0; i < n; ++i) {
    par_[i] = i;
    size_[i] = 1;
  }
}

int DSU::get(int x) {
  if (par_[x] != x) {
    par_[x] = get(par_[x]);
  }
  return par_[x];
}

void DSU::unite(int x, int y) {
  x = get(x);
  y = get(y);
  if (x == y) {
    return;
  }
  --set_cnt_;
  if (size_[x] > size_[y]) {
    std::swap(x, y);
  }
  par_[x] = y;
  size_[y] += size_[x];
}

int DSU::setSize(int x) {
  return size_[get(x)];
}

int DSU::setCount() {
  return set_cnt_;
}
