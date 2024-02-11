#include "precompiled.h"
#include "point.h"

Point::Point() : QPoint()
{}

Point::Point(int xpos, int ypos, QColor color, int size)
    : QPoint(xpos, ypos), color_(color), size_(size)
{}

Point::~Point()
{}
