#pragma once

#include <clustering/kmeans.h>

#include "central_widget.h"
#include "side_bar.h"
#include "data_view.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(int width, int height, QWidget* parent = nullptr);
    ~MainWindow();

private:
    QPalette createPalette(const QColor& backgroundColor);

    CentralWidget* centralWidget_ = nullptr;
    SideBar* sideBar_ = nullptr;
    DataView* dataView_ = nullptr;
    
    std::unique_ptr<Kmeans> kmeans_;

public slots:
    void cluster();
};

