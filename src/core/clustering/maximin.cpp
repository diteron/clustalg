#include "precompiled.h"

#include "maximin.h"

Maximin::Maximin(int xMax, int yMax, int pointsCnt) 
    : ClusteringAlgo(xMax, yMax, pointsCnt)
{
    clusters_ = std::vector<DataCluster>();
}

Maximin::~Maximin()
{}

void Maximin::cluster()
{
    // Create first cluster
    clusters_.push_back(DataCluster(points_[0]));
    this->reclusterPoints();
    
    // Create second cluster
    DataPoint farthestPointInFirstCluster = clusters_[0].getFarthestPoint();
    clusters_.push_back(DataCluster(farthestPointInFirstCluster));
    
    ultimateDistance_ = this->getDistanceBetweenPoints(clusters_[0].getCentroid(),
                                                       clusters_[1].getCentroid()) / 2;

    while (true) {
        this->clearClustersPoints();
        this->reclusterPoints();

        if (this->addNewCluster()) {
            this->recalculateUltimateDistance();
        }
        else {
            break;
        }
    }
}

void Maximin::reclusterPoints()
{
    unsigned int threadsCnt = std::thread::hardware_concurrency();
    unsigned int pointsPerThread = std::round(pointsCnt_ / threadsCnt);
    std::vector<std::thread> threads(threadsCnt);

    int currentFirstPointIdx = 0;
    int currentLastPointIdx = pointsPerThread - 1;
    
    for (auto& thread : threads) {
        if (currentLastPointIdx >= pointsCnt_) {
            currentLastPointIdx = pointsCnt_ - 1;
        }
        thread = std::thread(&Maximin::findClustersForPoints, this, currentFirstPointIdx, currentLastPointIdx);
        currentFirstPointIdx = currentLastPointIdx + 1;
        currentLastPointIdx += pointsPerThread;
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

void Maximin::findClustersForPoints(int firsPointIdx, int lastPointIdx)
{
    for (int i = firsPointIdx; i <= lastPointIdx; ++i) {
        int bestClusterIdx = -1;
        double minDistance = std::numeric_limits<double>::max();

        for (int j = 0; j < clusters_.size(); ++j) {
            double distance = this->getDistanceBetweenPoints(points_[i], clusters_[j].getCentroid());
            if (distance < minDistance) {
                minDistance = distance;
                bestClusterIdx = j;
            }
        }

        clusters_[bestClusterIdx].addPoint(points_[i], minDistance);

        if (points_[i].getClusterIdx() != bestClusterIdx) {
            points_[i].setClusterIdx(bestClusterIdx);
        }
    }
}

bool Maximin::addNewCluster()
{
    double maxDistToFarthestPoint = -1.0;
    size_t maxFarthestPntClusterIdx = 0;

    for (size_t i = 0; i < clusters_.size(); ++i) {
        double distToFarthestPnt = clusters_[i].getDistanceToFarthestPoint();

        if (distToFarthestPnt > ultimateDistance_ 
            && distToFarthestPnt > maxDistToFarthestPoint
            ) {
            maxDistToFarthestPoint = distToFarthestPnt;
            maxFarthestPntClusterIdx = i;
        }
    }

    bool isNewClusterFound = false;
    if (maxDistToFarthestPoint > 0) {
        clusters_.push_back(DataCluster(clusters_[maxFarthestPntClusterIdx].getFarthestPoint()));
        isNewClusterFound = true;
    }

    return isNewClusterFound;
}

void Maximin::recalculateUltimateDistance()
{
    size_t clustersCnt = clusters_.size();
    double sumOfDistances = 0.0;

    for (size_t i = 0; i < clustersCnt - 1; ++i) {
        for (size_t j = i + 1; j < clustersCnt; ++j) {
            sumOfDistances += this->getDistanceBetweenPoints(clusters_[i].getCentroid(),
                                                             clusters_[j].getCentroid());
        }
    }

    ultimateDistance_ = sumOfDistances / (clustersCnt * (clustersCnt - 1));
}
