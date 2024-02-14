#include <precompiled.h>

#include <ui/kmeans_app.h>
#include <ui/main_window.h>

int main(int argc, char** argv)
{
    KmeansApp app(argc, argv);
    
    const int width = 1220, height = 650;
    MainWindow mainWnd(width, height);
    mainWnd.setMinimumSize(900, 510);
    mainWnd.show();
    
    int result = app.exec();
    return result;
}
