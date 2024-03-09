#pragma once

class SideBar : public QWidget {

    Q_OBJECT

public:
    SideBar(QWidget* parent = nullptr);
    ~SideBar();

    int getDataPointsCnt() const;
    int getClassesCnt() const;

private:
    QSpinBox* createSpinBox(QWidget* parent, int maxWidth, int maxHeight,
                            int minValue, int maxValue, int defaultValue);
    QPushButton* createPushButton(QWidget* parent, const char* buttonText,
                                  int maxWidth, int maxHeight);

    QVBoxLayout* layout_ = nullptr;

    QLabel* dataPointsCntLabel_ = nullptr;
    QLabel* classesCntLabel_ = nullptr;
    QSpinBox* dataPointsCntSpinbox_ = nullptr;
    QSpinBox* classesCntSpinbox_ = nullptr;
    QPushButton* clusterButton_ = nullptr;
    QSpacerItem* spacer_ = nullptr;

    const int spinBoxesMaxHeight_ = 40;
    const int spinBoxesMaxWidth_ = 90;
    const int spacerWidth_ = 20;
    const int spacerHeight_ = 40;
    const int buttonsMaxHeight_ = 40;
    const int buttonsMaxWidth_ = 90;

private slots:
    void handleClusterButtonClick();

signals:
    void clusterButtonClicked();
};

