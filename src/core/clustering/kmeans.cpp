#include "precompiled.h"

#include <random>
#include <thread>

#include "kmeans.h"

Kmeans::Kmeans(int xMax, int yMax, int pointsCnt, int clustersCnt)
    : ClusteringAlgo(xMax, yMax, pointsCnt)
{
    clustersCnt_ = clustersCnt;
    clusters_ = std::vector<DataCluster>(clustersCnt_);
}

Kmeans::~Kmeans()
{}

void Kmeans::createRandomClusters()
{
    for (int i = 0; i < clustersCnt_; ++i) {
        clusters_[i].setRandomCentroid(xMax_, yMax_);
    }
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
            thread = std::thread(&Kmeans::findClustersForPoints, this, currentFirstPointIdx, currentLastPointIdx);
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

void Kmeans::findClustersForPoints(int firsPointIdx, int lastPointIdx)
{
    for (int i = firsPointIdx; i <= lastPointIdx; ++i) {
        int bestClusterIdx = -1;
        double minDistance = std::numeric_limits<double>::max();
        
        for (int j = 0; j < clustersCnt_; ++j) {
            double distance = this->getDistanceBetweenPoints(points_[i], clusters_[j].getCentroid());
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
