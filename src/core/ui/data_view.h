#pragma once

#include <clustering/data_point.h>
#include <clustering/data_cluster.h>

class DataView : public QWidget {
public:
    DataView(const QPalette& backgroundColor, QWidget* parent = nullptr);
    ~DataView();

    int getWidth() const;
    int getHeight() const;

    void drawClusters(std::vector<DataCluster>&& clusters);

private:
    void paintEvent(QPaintEvent* event) override;
    void drawCentroid(QPainter& painter, DataPoint centroid, const QColor& color);
    void drawPoints(QPainter& painter, const std::vector<DataPoint>& points, const QColor& color);

    std::vector<DataCluster> clusters_;
};
