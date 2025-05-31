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
    layout->addWidget(GameEngine);
    layout->addWidget(ExpectedHours);
    layout->addWidget(GameGenre);
    
}

VideogameDisplayWindow::~VideogameDisplayWindow(){}
