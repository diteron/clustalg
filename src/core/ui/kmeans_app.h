#pragma once

class KmeansApp : public QApplication {
public:
    KmeansApp(int& argc, char** argv);
    ~KmeansApp();

private:
    void setSystemColorScheme();
};
