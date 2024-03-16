#pragma once

#include "clustering_algo.h"

class Maximin : public ClusteringAlgo {
public:
    Maximin(int xMax, int yMax, int pointsCnt);
    ~Maximin();

    void cluster() override;

protected:
    void reclusterPoints();
    void findClustersForPoints(int firsPointIdx, int lastPointIdx);
    bool addNewCluster();

    void recalculateUltimateDistance();

    double ultimateDistance_ = 0.0;
};

