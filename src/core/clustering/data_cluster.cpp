#include "precompiled.h"

#include <random>

#include "data_cluster.h"

DataCluster::DataCluster() 
    : points_(), centroid_(), mutex_()
{}

DataCluster::~DataCluster()
{}

void DataCluster::setRandomCentroid(int xmax, int ymax)
{
    static std::time_t seed = std::time(nullptr);
    std::mt19937 randX(++seed);
    std::mt19937 randY(++seed);

    int x = randX() % xmax;
    int y = randY() % ymax;
    centroid_.setPos(x, y);
}

void DataCluster::addPoint(DataPoint point)
{
    std::lock_guard<std::mutex> lock(mutex_);
    points_.push_back(point);
}

void DataCluster::setCentroid(DataPoint centroid)
{
    centroid_ = centroid;
}

void DataCluster::recalculateCentroid()
{
    int xsum = 0, ysum = 0;
    for (const auto& point : points_) {
        xsum += point.getXpos();
        ysum += point.getYpos();
    }

    int xnew = static_cast<int>(std::round(xsum / points_.size()));
    int ynew = static_cast<int>(std::round(ysum / points_.size()));
    centroid_.setPos(xnew, ynew);
}

DataPoint DataCluster::getCentroid() const
{
    return centroid_;
}

const std::vector<DataPoint>& DataCluster::getPoints() const
{
    return points_;
}

void DataCluster::clearPoints()
{
    points_.clear();
    points_ = std::vector<DataPoint>();
}
