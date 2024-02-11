#pragma once

#include "data_point.h"

class DataCluster {
public:
    DataCluster();
    ~DataCluster();

    void setRandomCentroid(int xmax, int ymax);

    void addPoint(DataPoint point);
    void setCentroid(DataPoint centroid);

    DataPoint getCentroid() const;
    const std::vector<DataPoint>& getPoints() const;

    void clearPoints();

private:
    std::vector<DataPoint> points_;
    DataPoint centroid_;
};
