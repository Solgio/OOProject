#include "VideoDisplayWindow.h"
VideoDisplayWindow::VideoDisplayWindow():
    MultimediaDisplayWindow(),
    Duration("", this),
    Prequel("", this),
    Sequel("", this)
{
    this->format();
}

VideoDisplayWindow::VideoDisplayWindow(Video *video):
    MultimediaDisplayWindow(video),
    Duration(QString::number(video->getDuration()), this),
    Prequel(QString::number(video->getPrequel()), this),
    Sequel(QString::number(video->getSequel()), this)
{
    this->format();
}

void VideoDisplayWindow::format(){

}
