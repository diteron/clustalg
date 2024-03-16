#pragma once

#include "clustering_algo.h"

class Kmeans : public ClusteringAlgo {
public:
    Kmeans(int xMax, int yMax, int pointsCnt, int clustersCnt);
    ~Kmeans();

    void createRandomClusters();

    void cluster() override;

protected:
    void findClustersForPoints(int firsPointIdx, int lastPointIdx);

    std::atomic<bool> isClustersChanged_ = true;
};
