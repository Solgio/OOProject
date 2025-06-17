#include "VideogameDisplayWindow.h"
#include "../../Model/lib/VideoGame.h"

VideogameDisplayWindow::VideogameDisplayWindow(VideoGame *vgame):
    MultimediaDisplayWindow(vgame),
    GameEngine(new QLabel(QString::fromStdString(vgame->getGameEngine()))),
    ExpectedHours(new QLabel(QString::number(vgame->getExpectedHours()))),
    GameGenre(new QLabel(QString::fromStdString(vgame->getGameType())))
{
    this->format();
}

void VideogameDisplayWindow::format(){
    layout = AttributeDisplayWindow::getDetailLayout();

    auto *GELayout = new QFormLayout();
    GELayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("GameEngine : ")), GameEngine);
    layout->addLayout(GELayout);
    //layout->addWidget(Pages);

    auto *EHLayout = new QFormLayout();
    EHLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("ExpectedHours : ")), ExpectedHours);
    layout->addLayout(EHLayout);
    //layout->addWidget(Volume);

    auto *GGLayout = new QFormLayout();
    GGLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("GameGenre : ")), GameGenre);
    layout->addLayout(GGLayout);

    //layout->addWidget(GameEngine);
    //layout->addWidget(ExpectedHours);
    //layout->addWidget(GameGenre);
    
}

VideogameDisplayWindow::~VideogameDisplayWindow(){}
