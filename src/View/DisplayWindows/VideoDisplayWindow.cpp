#include "VideoDisplayWindow.h"
#include "../../Model/lib/Video.h"

VideoDisplayWindow::VideoDisplayWindow(Video *video):
    MultimediaDisplayWindow(video),
    Duration(new QLabel(QString::number(video->getDuration()))),
    Prequel(new QLabel(QString::number(video->getPrequel()))),
    Sequel(new QLabel(QString::number(video->getSequel())))
{
    format();
}

void VideoDisplayWindow::format(){
    layout = new QVBoxLayout(this);
    layout->addWidget(Duration);
    layout->addWidget(Prequel);
    layout->addWidget(Sequel);
    AttributeDisplayWindow::getDetailLayout()->addLayout(layout);
}

VideoDisplayWindow::~VideoDisplayWindow(){}
