#include "generator/distribution.h"
#include "generator/normal_distribution.h"
#include "generator/discrete_distribution.h"

#include "generator/generator.h"
#include "generator/random.h"
#include "generator/grid.h"
#include "generator/dual_homed.h"
#include "generator/fat_tree.h"

#include "algorithm/square_dijkstra.h"
#include "algorithm/set_dijkstra.h"
#include "algorithm/pq_dijkstra.h"
#include "algorithm/bfs.h"
#include "algorithm/bfs_dag.h"
#include "algorithm/limited_dijkstra.h"
#include "algorithm/cluster_dijkstra.h"

#include "testing/validator.h"

#include "util/util.h"

#include <iostream>
#include <iomanip>
#include <vector>

int main() {
  Debug::enable();
  std::cout << std::fixed << std::setprecision(2);

  const std::vector<std::pair<double, double>> discrete_probas = {
      {100, 80},
      {200, 4},
      {300, 4},
      {500, 4},
      {1000, 4},
      {2000, 4},
  };

  std::unique_ptr<Distribution> norm_distrib = std::make_unique<NormalDistribution>(7.5, 1.25);
  std::unique_ptr<Distribution> discr_distrib = std::make_unique<DiscreteDistribution>(discrete_probas);

  auto rnd_gen = std::make_unique<RandomGraphGenerator>(50, 200);
  auto grid_gen = std::make_unique<GridGenerator>(80, true);
  auto dual_homed_gen = std::make_unique<DualHomedGenerator>(15000, true);
  auto fat_tree_gen = std::make_unique<FatTreeGenerator>(28, true);

  auto square_dijkstra = std::make_unique<SquareDijkstraAlgorithm>();
  auto set_dijkstra = std::make_unique<SetDijkstraAlgorithm>();
  auto pq_dijkstra = std::make_unique<PqDijkstraAlgorithm>();

  auto bfs = std::make_unique<BfsAlgorithm>();
  auto bfs_dag = std::make_unique<BfsDagAlgorithm>();
  auto limited_dijkstra = std::make_unique<LimitedDijkstraAlgorithm>(501);
  auto cluster_dijkstra = std::make_unique<ClusteredDijkstraAlgorithm>(200);

  evaluateAlgo(
      fat_tree_gen.get(),
      discr_distrib.get(),
      /* algo = */ limited_dijkstra.get(),
      /* best = */ pq_dijkstra.get()
  );

  return 0;
}
