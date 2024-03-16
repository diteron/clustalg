#pragma once

#include "data_cluster.h"

class ClusteringAlgo {
public:    
    void setXmax(int xMax);
    void setYmax(int yMax);
    void setPointsCnt(int cnt);
    void setClustersCnt(int cnt);

    void createRandomPoints();
    virtual void clearData();

    virtual void cluster() = 0;

    std::vector<DataCluster>& getClusters();

protected:
    ClusteringAlgo(int xMax, int yMax, int pointsCnt);

    void clearClustersPoints();
    double getDistanceBetweenPoints(DataPoint p1, DataPoint p2) const;

    int xMax_ = 0;
    int yMax_ = 0;
    int pointsCnt_ = 0;
    int clustersCnt_ = 0;

    std::vector<DataPoint> points_;
    std::vector<DataCluster> clusters_;
};

