#include "precompiled.h"
#include "data_view.h"

DataView::DataView(const QPalette& backgroundColor, QWidget* parent)
    : QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setPalette(backgroundColor);
}

DataView::~DataView()
{}

int DataView::getWidth() const
{
    return this->width();
}

int DataView::getHeight() const
{
    return this->height();
}

void DataView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.begin(this);

    QColor color;
    int hue = 0;
    int hueAdd = clusters_.size() > 0 ? static_cast<int>(360 / clusters_.size()) : 0;
    color.setHsv(hue, 180, 180);

    for (auto& cluster : clusters_) {
        this->drawCentroid(painter, cluster.getCentroid(), color);
        this->drawPoints(painter, cluster.getPoints(), color);
        
        hue += hueAdd;
        color.setHsv(hue, 180, 180);
    }

    painter.end();
}

void DataView::drawCentroid(QPainter& painter, DataPoint centroid, const QColor& color)
{
    QPen pen = QPen(QBrush(color), 12, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(pen);
    painter.drawPoint(centroid.getXpos(), centroid.getYpos());
}

void DataView::drawPoints(QPainter& painter, const std::vector<DataPoint>& points, const QColor& color)
{
    QPen pen = QPen(QBrush(color), 2, Qt::SolidLine);
    painter.setPen(pen);

    for (auto point : points) {
        painter.drawPoint(point.getXpos(), point.getYpos());
    }
}

void DataView::drawClusters(std::vector<DataCluster>&& clusters)
{
    clusters_ = std::move(clusters);
    this->update();
}
