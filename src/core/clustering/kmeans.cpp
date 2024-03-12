#include "precompiled.h"

#include <random>
#include <thread>

#include "kmeans.h"

Kmeans::Kmeans(int xMax, int yMax, int pointsCnt, int clustersCnt)
    : xMax_(xMax), yMax_(yMax),
      pointsCnt_(pointsCnt), clustersCnt_(clustersCnt), 
      points_(pointsCnt_), clusters_(clustersCnt_)
{}

Kmeans::~Kmeans()
{}

void Kmeans::setXmax(int xMax)
{
    xMax_ = xMax;
}

void Kmeans::setYmax(int yMax)
{
    yMax_ = yMax;
}

void Kmeans::setPointsCnt(int cnt)
{
    pointsCnt_ = cnt;
    points_ = std::vector<DataPoint>(pointsCnt_);
}

void Kmeans::setClustersCnt(int cnt)
{
    clustersCnt_ = cnt;
    clusters_ = std::vector<DataCluster>(clustersCnt_);
}

void Kmeans::createRandomPoints()
{
    for (int i = 0; i < pointsCnt_; ++i) {
        points_[i].setRandomPos(xMax_, yMax_);
    }
}

void Kmeans::createRandomClusters()
{
    for (int i = 0; i < clustersCnt_; ++i) {
        clusters_[i].setRandomCentroid(xMax_, yMax_);
    }
}

void Kmeans::clearData()
{
    xMax_ = 0;
    yMax_ = 0;
    pointsCnt_ = 0;
    clustersCnt_ = 0;
    points_.clear();
    clusters_.clear();
}

void Kmeans::cluster()
{
    unsigned int threadsCnt = std::thread::hardware_concurrency();
    unsigned int pointsPerThread = std::round(pointsCnt_ / threadsCnt);

    isClustersChanged_ = true;
    while (isClustersChanged_.load()) {
        isClustersChanged_ = false;

        std::vector<std::thread> threads(threadsCnt);
        int currentFirstPointIdx = 0;
        int currentLastPointIdx = pointsPerThread - 1;
        for (auto& thread : threads) {
            if (currentLastPointIdx >= pointsCnt_) {
                currentLastPointIdx = pointsCnt_ - 1;
            }
            thread = std::thread(&Kmeans::findClusterForPoints, this, currentFirstPointIdx, currentLastPointIdx);
            currentFirstPointIdx = currentLastPointIdx + 1;
            currentLastPointIdx += pointsPerThread;
        }

        for (auto& thread : threads) {
            thread.join();
        }

        if (isClustersChanged_.load()) {
            for (auto& cluster : clusters_) {
                cluster.recalculateCentroid();
            }
            this->clearClustersPoints();
        }
    }
}

std::vector<DataCluster>& Kmeans::getClusters()
{
    return clusters_;
}

void Kmeans::findClusterForPoints(int firsPointIdx, int lastPointIdx)
{
    for (int i = firsPointIdx; i <= lastPointIdx; ++i) {
        int bestClusterIdx = -1;
        double minDistance = std::numeric_limits<double>::max();
        
        for (int j = 0; j < clustersCnt_; ++j) {
            double distance = getDistanceBetweenPoints(points_[i], clusters_[j].getCentroid());
            if (distance < minDistance) {
                minDistance = distance;
                bestClusterIdx = j;
            }
        }

        clusters_[bestClusterIdx].addPoint(points_[i]);
        if (points_[i].getClusterIdx() != bestClusterIdx) {
            points_[i].setClusterIdx(bestClusterIdx);
            isClustersChanged_ = true;
        }
    }
}

void Kmeans::clearClustersPoints()
{
    for (auto& cluster : clusters_) {
        cluster.clearPoints();
    }
}

double Kmeans::getDistanceBetweenPoints(DataPoint p1, DataPoint p2)
{
    return std::sqrt( std::pow((p1.getXpos() - p2.getXpos()), 2) + std::pow((p1.getYpos() - p2.getYpos()), 2) );
}
