#include "precompiled.h"
#include "side_bar.h"

SideBar::SideBar(QWidget* parent) : QWidget(parent)
{
    layout_ = new QVBoxLayout(this);

    dataPointsCntLabel_ = new QLabel("Number of data points:", this);
    dataPointsCntSpinbox_ = createSpinBox(this, spinBoxesMaxWidth_, spinBoxesMaxHeight_,
                                          1'000, 1000'000, 10'000);
    layout_->addWidget(dataPointsCntLabel_);
    layout_->addWidget(dataPointsCntSpinbox_);

    classesCntLabel_ = new QLabel("Number of classes:", this);
    classesCntSpinbox_ = createSpinBox(this, spinBoxesMaxWidth_, spinBoxesMaxHeight_,
                                       2, 20, 5);
    layout_->addWidget(classesCntLabel_);
    layout_->addWidget(classesCntSpinbox_);

    clusterButton_ = createPushButton(this, "Cluster",
                                      buttonsMaxWidth_, buttonsMaxHeight_);
    clusterButton_->connect(clusterButton_, &QPushButton::clicked, this, &SideBar::handleClusterButtonClick);
    layout_->addWidget(clusterButton_);

    spacer_ = new QSpacerItem(spacerWidth_, spacerHeight_, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout_->addItem(spacer_);
}

SideBar::~SideBar()
{}

int SideBar::getDataPointsCnt() const
{
    return dataPointsCntSpinbox_->value();
}

int SideBar::getClassesCnt() const
{
    return classesCntSpinbox_->value();
}

QSpinBox* SideBar::createSpinBox(QWidget* parent, int maxWidth, int maxHeight,
                                 int minValue, int maxValue, int defaultValue)
{
    QSpinBox* spinBox = new QSpinBox(parent);
    spinBox->setMaximumSize(QSize(maxWidth, maxHeight));
    spinBox->setRange(minValue, maxValue);
    spinBox->setValue(defaultValue);
    return spinBox;
}

QPushButton* SideBar::createPushButton(QWidget* parent, const char* buttonText,
                                       int maxWidth, int maxHeight) 
{
    QPushButton* pushButton = new QPushButton(buttonText, parent);
    pushButton->setMaximumSize(QSize(maxWidth, maxHeight));
    return pushButton;
}

void SideBar::handleClusterButtonClick()
{
    emit clusterButtonClicked();
}
