#include "precompiled.h"

#include <random>

#include "data_point.h"

DataPoint::DataPoint()
{}

DataPoint::DataPoint(int xpos, int ypos, int clusterIdx)
    : xpos_(xpos), ypos_(ypos), clusterIdx_(clusterIdx)
{}

DataPoint::~DataPoint()
{}

void DataPoint::setPos(int xpos, int ypos)
{
    xpos_ = xpos;
    ypos_ = ypos;
}

void DataPoint::setXpos(int xpos)
{
    xpos_ = xpos;
}

void DataPoint::setYpos(int ypos)
{
    ypos_ = ypos;
}

void DataPoint::setRandomPos(int xmax, int ymax)
{
    static std::time_t seed = std::time(nullptr);
    std::mt19937 randX(++seed);
    std::mt19937 randY(++seed);
    
    int x = randX() % xmax;
    int y = randY() % ymax;
    this->setPos(x, y);
}

void DataPoint::setClusterIdx(int cidx)
{
    clusterIdx_ = cidx;
}

int DataPoint::getXpos() const
{
    return xpos_;
}

int DataPoint::getYpos() const
{
    return ypos_;
}

int DataPoint::getClusterIdx() const
{
    return clusterIdx_;
}
