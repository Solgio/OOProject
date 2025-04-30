#include "FilmDisplayWindow.h"

FilmDisplayWindow::FilmDisplayWindow():
    VideoDisplayWindow(),
    Producer("", this),
    Photoproducer("", this)
{
    this->format();
}

FilmDisplayWindow::FilmDisplayWindow(Film *film):
    VideoDisplayWindow(film),
    Producer(QString::fromStdString(film->getProducer()), this),
    Photoproducer(QString::fromStdString(film->getPhotoDirector()), this)
{
    this->format();
}

void FilmDisplayWindow::format(){

}
