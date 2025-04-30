#include "VideogameDisplayWindow.h"

VideogameDisplayWindow::VideogameDisplayWindow():
    MultimediaDisplayWindow(),
    GameEngine("", this),
    ExpectedHours("", this),
    GameGenre("", this)
{
    this->format();
}

VideogameDisplayWindow::VideogameDisplayWindow(VideoGame *vgame):
    MultimediaDisplayWindow(vgame),
    GameEngine(QString::fromStdString(vgame->getGameEngine()), this),
    ExpectedHours(QString::number(vgame->getExpectedHours()), this),
    GameGenre(QString::fromStdString(vgame->getGameType()), this)
{
    this->format();
}

void VideogameDisplayWindow::format(){

}
