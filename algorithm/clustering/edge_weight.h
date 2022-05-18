#pragma once

#include "algorithm/clustering/clustering.h"

#include "graph/graph.h"

Clustering clusterByEdgeWeights(const Graph& g, int size_limit);
