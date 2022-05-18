#include "cluster_dijkstra.h"

#include "algorithm/clustering/edge_weight.h"

#include <vector>
#include <queue>

ClusteredDijkstraAlgorithm::ClusteredDijkstraAlgorithm(int cluster_size_limit):
    cluster_size_limit_(cluster_size_limit) {}

Solution ClusteredDijkstraAlgorithm::solve(const Graph &g, int source) {
  const auto clustering = clusterByEdgeWeights(g, cluster_size_limit_);
  const int cc = clustering.nodes_of_cluster.size();
  const int src_cl = clustering.cluster[source];

  std::vector<Edge> local_result(g.n());
  // Intra-cluster Dijkstra
  {
    std::vector<double> dist(g.n(), std::numeric_limits<double>::max());
    std::vector<bool> used(g.n());
    std::priority_queue<std::pair<double, int>> q;

    dist[source] = 0;
    q.emplace(-dist[source], source);

    while (!q.empty()) {
      auto p = q.top();
      p.first = -p.first;
      q.pop();

      if (used[p.second]) {
        continue;
      }
      used[p.second] = true;

      for (const auto& e : g.getEdges(p.second)) {
        if (clustering.cluster[e.dst] == src_cl && !used[e.dst]) {
          if (dist[p.second] + e.length < dist[e.dst]) {
            dist[e.dst] = dist[p.second] + e.length;

            if (p.second == source) {
              local_result[e.dst] = e;
            } else {
              local_result[e.dst] = local_result[p.second];
            }

            q.emplace(-dist[e.dst], e.dst);
          }
        }
      }
    }
  }

  std::vector<Edge> global_result(cc);
  // Inter-cluster Dijkstra
  {
    std::vector<double> dist(cc, std::numeric_limits<double>::max());
    std::vector<bool> used(cc);
    std::priority_queue<std::pair<double, int>> q;

    dist[src_cl] = 0;
    q.emplace(-dist[src_cl], src_cl);

    while (!q.empty()) {
      auto p = q.top();
      p.first = -p.first;
      q.pop();

      if (used[p.second]) {
        continue;
      }
      used[p.second] = true;

      for (int v : clustering.nodes_of_cluster[p.second]) {
        for (const auto &e: g.getEdges(v)) {
          int dst_cl = clustering.cluster[e.dst];
          if (dst_cl != src_cl && !used[dst_cl]) {
            if (dist[p.second] + e.length < dist[dst_cl]) {
              dist[dst_cl] = dist[p.second] + e.length;

              if (p.second == src_cl) {
                global_result[dst_cl] = e;
              } else {
                global_result[dst_cl] = global_result[p.second];
              }

              q.emplace(-dist[dst_cl], dst_cl);
            }
          }
        }
      }
    }
  }

  std::vector<Edge> result(g.n());
  for (int t = 0; t < g.n(); ++t) {
    if (t == source) {
      continue;
    }

    if (clustering.cluster[t] == src_cl) {
      result[t] = local_result[t];
    } else {
      auto global_edge = global_result[clustering.cluster[t]];
      if (global_edge.src == source) {
        result[t] = global_edge;
      } else {
        result[t] = local_result[global_edge.src];
      }
    }
  }

  return Solution{ .next_hop = std::move(result) };
}

std::string ClusteredDijkstraAlgorithm::name() const {
  return "Clustered Dijkstra (" + std::to_string(cluster_size_limit_) + ")";
}
