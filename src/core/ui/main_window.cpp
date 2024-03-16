#include "precompiled.h"
#include "main_window.h"

MainWindow::MainWindow(int width, int height, QWidget* parent) 
    : QMainWindow(parent)
{
    this->resize(width, height);
    centralWidget_ = new CentralWidget(this);
    this->setCentralWidget(centralWidget_);

    sideBar_ = new SideBar(centralWidget_);
    sideBar_->connect(sideBar_, &SideBar::clusterButtonClicked, this, &MainWindow::cluster);
    centralWidget_->addWidget(sideBar_, 1);

    Qt::ColorScheme systemColorScheme = qApp->styleHints()->colorScheme();
    QColor dataViewColor = (systemColorScheme == Qt::ColorScheme::Dark) ? QColor(220, 224, 227) : Qt::white;

    dataView_ = new DataView(createPalette(dataViewColor), centralWidget_);
    centralWidget_->addWidget(dataView_, 5);

    kmeans_ = std::make_unique<Kmeans>(dataView_->getWidth(), dataView_->getHeight(),
                                       sideBar_->getDataPointsCnt(), sideBar_->getClustersCnt());
    maximin_ = std::make_unique<Maximin>(dataView_->getWidth(), dataView_->getHeight(),
                                         sideBar_->getDataPointsCnt());
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

void MainWindow::cluster()
{
    QString algorithm = sideBar_->getClusteringAlgorithm();

    if (algorithm == "Kmeans") {
        kmeans_->clearData();
        kmeans_->setXmax(dataView_->getWidth());
        kmeans_->setYmax(dataView_->getHeight());
        kmeans_->setPointsCnt(sideBar_->getDataPointsCnt());
        kmeans_->setClustersCnt(sideBar_->getClustersCnt());
        kmeans_->createRandomPoints();
        kmeans_->createRandomClusters();
        kmeans_->cluster();

        dataView_->drawClusters(std::move(kmeans_->getClusters()));
    }
    else if (algorithm == "Maximin") {
        maximin_->clearData();
        maximin_->setXmax(dataView_->getWidth());
        maximin_->setYmax(dataView_->getHeight());
        maximin_->setPointsCnt(sideBar_->getDataPointsCnt());
        maximin_->createRandomPoints();
        maximin_->cluster();

        dataView_->drawClusters(std::move(maximin_->getClusters()));
    }
}
