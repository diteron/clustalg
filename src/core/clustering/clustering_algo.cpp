#include "precompiled.h"

#include <random>

#include "clustering_algo.h"

void ClusteringAlgo::setXmax(int xMax)
{
    xMax_ = xMax;
}

void ClusteringAlgo::setYmax(int yMax)
{
    yMax_ = yMax;
}

void ClusteringAlgo::setPointsCnt(int cnt)
{
    pointsCnt_ = cnt;
    points_ = std::vector<DataPoint>(pointsCnt_);
}

void ClusteringAlgo::setClustersCnt(int cnt)
{
    clustersCnt_ = cnt;
    clusters_ = std::vector<DataCluster>(clustersCnt_);
}

void ClusteringAlgo::createRandomPoints()
{
    std::random_device rdseed;
    std::mt19937 rand(rdseed());

    for (int i = 0; i < pointsCnt_; ++i) {
        int x = rand() % xMax_;
        int y = rand() % yMax_;
        points_[i].setPos(x, y);
    }
}

void ClusteringAlgo::clearData()
{
    xMax_ = 0;
    yMax_ = 0;
    pointsCnt_ = 0;
    clustersCnt_ = 0;
    points_.clear();
    clusters_.clear();
}

std::vector<DataCluster>& ClusteringAlgo::getClusters()
{
    return clusters_;
}

ClusteringAlgo::ClusteringAlgo(int xMax, int yMax, int pointsCnt)
    : xMax_(xMax), yMax_(yMax),
      pointsCnt_(pointsCnt),
      points_(pointsCnt_)
{}

void ClusteringAlgo::clearClustersPoints()
{
    for (auto& cluster : clusters_) {
        cluster.clearPoints();
    }
}

double ClusteringAlgo::getDistanceBetweenPoints(DataPoint p1, DataPoint p2) const
{
    return std::sqrt(std::pow((p1.getXpos() - p2.getXpos()), 2) + std::pow((p1.getYpos() - p2.getYpos()), 2));
}
