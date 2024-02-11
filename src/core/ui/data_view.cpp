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
    painter.end();
}

void DataView::drawClusters(std::vector<DataCluster>& clusters)
{
}

QPen DataView::createPen(int width, Qt::PenStyle style, const QColor& color)
{
    return QPen();
}
