#include "SerieDisplayWindow.h"

SerieDisplayWindow::SerieDisplayWindow():
    VideoDisplayWindow(),
    Seasons("", this),
    Episodes("", this),
    Creator("", this),
    Finished("", this)
{
    this->format();
}
SerieDisplayWindow::SerieDisplayWindow(Serie *serie):
    VideoDisplayWindow(serie),
    Seasons(QString::number(serie->getSeasons()), this),
    Episodes(QString::number(serie->getEpisodes()), this),
    Creator(QString::fromStdString(serie->getCreator()), this),
    Finished(serie->getFinished() ? "Yes" : "No")
{
    this->format();
}

void SerieDisplayWindow::format(){

}
