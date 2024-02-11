#include "precompiled.h"

#include <random>

#include "data_cluster.h"

DataCluster::DataCluster() 
    : points_(), centroid_()
{}

DataCluster::~DataCluster()
{}

void DataCluster::setRandomCentroid(int xmax, int ymax)
{
    std::mt19937 randX(std::time(nullptr));
    std::mt19937 randY(std::time(nullptr));
    int x = randX() % xmax;
    int y = randY() % ymax;
    centroid_.setPos(x, y);
}

void DataCluster::addPoint(DataPoint point)
{
    points_.push_back(point);
}

void DataCluster::setCentroid(DataPoint centroid)
{
    centroid_ = centroid;
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
}
