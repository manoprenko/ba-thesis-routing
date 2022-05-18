#pragma once

#include "graph/edge.h"

#include <string>
#include <vector>

class GraphBuilder;
class EdgeRange;

class Graph {
  friend class GraphBuilder;

public:
  [[nodiscard]] size_t n() const;

  [[nodiscard]] size_t m() const;

  [[nodiscard]] EdgeRange getEdges(size_t v) const;

  [[nodiscard]] const Edge* findEdge(size_t from, size_t to) const;

  [[nodiscard]] std::string graphViz() const;

private:
  explicit Graph(GraphBuilder builder);

private:
  size_t n_;
  std::vector<Edge> edges_;
  std::vector<size_t> first_edge_;
};

class EdgeRange {
public:
  EdgeRange(const std::vector<Edge>& edges, size_t first, size_t last);

  std::vector<Edge>::const_iterator begin();

  std::vector<Edge>::const_iterator end();

private:
  const std::vector<Edge>& edges_;
  size_t first_ = 0;
  size_t last_ = 0;
};
