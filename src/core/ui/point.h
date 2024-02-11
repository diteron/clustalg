#pragma once

class Point : public QPoint {
public:
    Point();
    Point(int xpos, int ypos, QColor color = Qt::black, int size = 2);
    ~Point();

private:
    QColor color_ = Qt::black;
    int size_ = 2;
};

