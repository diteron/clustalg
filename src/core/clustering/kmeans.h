#pragma once

#include "data_cluster.h"

class Kmeans {
public:
    Kmeans(int xMax, int yMax, int pointsCnt, int clustersCnt);
    ~Kmeans();

    void setXmax(int xMax);
    void setYmax(int yMax);
    void setPointsCnt(int cnt);
    void setClustersCnt(int cnt);

    void createRandomPoints();
    void createRandomClusters();

    void clearData();

    void cluster();

    std::vector<DataCluster>& getClusters();

private:
    void findClusterForPoints(int firsPointIdx, int lastPointIdx);
    void clearClustersPoints();
    double getDistanceBetweenPoints(DataPoint p1, DataPoint p2);

    int xMax_ = 0;
    int yMax_ = 0;
    int pointsCnt_ = 0;
    int clustersCnt_ = 0;

    std::vector<DataPoint> points_;
    std::vector<DataCluster> clusters_;

    std::atomic<bool> isClustersChanged_ = true;
};

