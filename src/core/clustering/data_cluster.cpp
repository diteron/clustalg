#include "precompiled.h"

#include <random>

#include "data_cluster.h"

DataCluster::DataCluster() 
    : points_(), centroid_(), mutex_()
{}

DataCluster::DataCluster(DataPoint centroid) 
    : points_(), centroid_(centroid), mutex_()
{}

DataCluster::DataCluster(const DataCluster& other)
{
    points_ = other.points_;
    centroid_ = other.centroid_;
    distToFarthestPoint_ = other.distToFarthestPoint_.load();
    farthestPointIdx_ = other.farthestPointIdx_.load();
}

DataCluster::DataCluster(DataCluster&& other) noexcept
{
    points_ = std::move(other.points_);
    centroid_ = std::move(other.centroid_);
    distToFarthestPoint_ = other.distToFarthestPoint_.load();
    farthestPointIdx_ = other.farthestPointIdx_.load();
}

DataCluster::~DataCluster()
{}

void DataCluster::setRandomCentroid(int xmax, int ymax)
{
    std::random_device rdseed;
    std::mt19937 rand(rdseed());

    int x = rand() % xmax;
    int y = rand() % ymax;
    centroid_.setPos(x, y);
}

void DataCluster::addPoint(DataPoint point)
{
    std::lock_guard<std::mutex> lock(mutex_);
    points_.push_back(point);
}

void DataCluster::addPoint(DataPoint point, double distToCentroid)
{
    std::lock_guard<std::mutex> lock(mutex_);
    points_.push_back(point);

    if (distToCentroid > distToFarthestPoint_.load()) {
        distToFarthestPoint_ = distToCentroid;
        farthestPointIdx_ = points_.size() - 1;
    }
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

size_t DataCluster::getPointsCnt() const
{
    return points_.size();
}

const DataPoint& DataCluster::getFarthestPoint() const
{
    return points_[farthestPointIdx_];
}

double DataCluster::getDistanceToFarthestPoint() const
{
    return distToFarthestPoint_;
}

void DataCluster::clearPoints()
{
    points_.clear();
    points_ = std::vector<DataPoint>();

    distToFarthestPoint_ = -1.0;
    farthestPointIdx_ = -1.0;
}
