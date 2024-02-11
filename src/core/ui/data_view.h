#pragma once

#include <clustering/data_point.h>
#include <clustering/data_cluster.h>

class DataView : public QWidget {
public:
    DataView(const QPalette& backgroundColor, QWidget* parent = nullptr);
    ~DataView();

    int getWidth() const;
    int getHeight() const;

private:
    void paintEvent(QPaintEvent* event) override;
    void drawClusters(std::vector<DataCluster>& clusters);
    QPen createPen(int width, Qt::PenStyle style, const QColor& color);
};
