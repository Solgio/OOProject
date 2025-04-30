#include "MultimediaDisplayWindow.h"

MultimediaDisplayWindow::MultimediaDisplayWindow():
    AttributeDisplayWindow(),
    Producer("", this),
    Platforms("", this)
{
    this->format();
}

MultimediaDisplayWindow::MultimediaDisplayWindow(Multimedia *multm):
    AttributeDisplayWindow(multm),
    Producer(QString::fromStdString(multm->getProducer()), this),
    Platforms(QString::fromStdString(multm->getPlatforms()), this)
{
    this->format();
}

void MultimediaDisplayWindow::format(){

}
