#pragma once

#include <mutex>

#include "data_point.h"

class DataCluster {
public:
    DataCluster();
    DataCluster(DataPoint centroid);
    DataCluster(const DataCluster& other);
    DataCluster(DataCluster&& other) noexcept;
    ~DataCluster();

    void setRandomCentroid(int xmax, int ymax);

    void addPoint(DataPoint point);
    void addPoint(DataPoint point, double distToCentroid);
    void setCentroid(DataPoint centroid);

    void recalculateCentroid();

    DataPoint getCentroid() const;
    const std::vector<DataPoint>& getPoints() const;
    size_t getPointsCnt() const;

    const DataPoint& getFarthestPoint() const;
    double getDistanceToFarthestPoint() const;

    void clearPoints();

private:
    std::vector<DataPoint> points_;
    DataPoint centroid_;

    std::atomic<double> distToFarthestPoint_ = -1.0;
    std::atomic<size_t> farthestPointIdx_ = -1.0;

    mutable std::mutex mutex_;
};
