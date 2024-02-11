#include <precompiled.h>

#include "kmeans_app.h"

KmeansApp::KmeansApp(int& argc, char** argv) : QApplication(argc, argv)
{

#ifdef Q_OS_WIN
    setSystemColorScheme();
#endif

}

KmeansApp::~KmeansApp()
{}

void KmeansApp::setSystemColorScheme()
{
    Qt::ColorScheme systemColorScheme = qApp->styleHints()->colorScheme();
    if (systemColorScheme == Qt::ColorScheme::Dark) {
        this->setStyle(QStyleFactory::create("fusion"));
    }
}