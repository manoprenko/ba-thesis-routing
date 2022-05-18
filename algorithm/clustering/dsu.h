#pragma once

#include <vector>

class DSU {
public:
  explicit DSU(int n);

  int get(int x);

  void unite(int x, int y);

  int setSize(int x);

  int setCount();

private:
  std::vector<int> par_;
  std::vector<int> size_;
  int set_cnt_;
};
