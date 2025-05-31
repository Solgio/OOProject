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
    layout = AttributeDisplayWindow::getDetailLayout();
    layout->addWidget(Duration);
    layout->addWidget(Prequel);
    layout->addWidget(Sequel);
    
}

VideoDisplayWindow::~VideoDisplayWindow(){}
