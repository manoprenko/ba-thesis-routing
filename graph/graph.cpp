#include "graph.h"

#include "graph/graph_builder.h"
#include "graph/edge.h"

#include "util/util.h"

#include <algorithm>
#include <sstream>
#include <string>

Graph::Graph(GraphBuilder builder) :
    n_(builder.n_),
    edges_(std::move(builder.edge_list_)),
    first_edge_(n_ + 1) {
  std::sort(edges_.begin(), edges_.end(), [](const Edge& lhs, const Edge& rhs) {
    return lhs.src < rhs.src;
  });

  size_t current_edge = 0;
  for (int src = 0; src < n_; ++src) {
    first_edge_[src] = current_edge;
    while (current_edge < edges_.size() && edges_[current_edge].src == src) {
      ++current_edge;
    }
  }
  first_edge_[n_] = current_edge;
  ASSERT(current_edge == edges_.size(), "Wrong bucket heads");
}

size_t Graph::n() const {
  return n_;
}

size_t Graph::m() const {
  return edges_.size();
}

EdgeRange Graph::getEdges(size_t v) const {
  return {edges_, first_edge_[v], first_edge_[v + 1]};
}

const Edge* Graph::findEdge(size_t from, size_t to) const {
  for (const auto& e : getEdges(from)) {
    if (e.dst == to) {
      return &e;
    }
  }
  return nullptr;
}

std::string Graph::graphViz() const {
  std::stringstream os;
  os << "digraph G {\n";
  for (int i = 0; i < n(); ++i) {
    os << "\n";
    for (const auto& e : getEdges(i)) {
      os << "  " << e.src << " -> " << e.dst << " [label=\"" << e.length << "\"]\n";
    }
  }
  os << "}";

  return os.str();
}

EdgeRange::EdgeRange(const std::vector<Edge>& edges, size_t first, size_t last):
    edges_(edges),
    first_(first),
    last_(last) {}

std::vector<Edge>::const_iterator EdgeRange::begin() {
  return edges_.begin() + first_;
}

std::vector<Edge>::const_iterator EdgeRange::end() {
  return edges_.begin() + last_;
}
