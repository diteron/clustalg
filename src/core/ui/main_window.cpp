#include "precompiled.h"
#include "main_window.h"

MainWindow::MainWindow(int width, int height, QWidget* parent) 
    : QMainWindow(parent)
{
    this->resize(width, height);
    centralWidget_ = new CentralWidget(this);
    this->setCentralWidget(centralWidget_);

    sideBar_ = new SideBar(centralWidget_);
    centralWidget_->addWidget(sideBar_, 1);

    dataView_ = new DataView(createPalette(Qt::white), centralWidget_);
    centralWidget_->addWidget(dataView_, 5);
}

MainWindow::~MainWindow()
{}

QPalette MainWindow::createPalette(const QColor& backgroundColor)
{
    QPalette palette;
    QBrush brush(backgroundColor);
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Window, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
    return palette;
}
