#include "MultimediaDisplayWindow.h"
#include "../../Model/lib/Multimedia.h"

MultimediaDisplayWindow::MultimediaDisplayWindow(Multimedia *multm):
    AttributeDisplayWindow(multm),
    Producer(new QLabel(QString::fromStdString(multm->getProducer()))),
    Platforms(new QLabel(QString::fromStdString(multm->getPlatforms())))
{
    format();
}

void MultimediaDisplayWindow::format(){
    layout = AttributeDisplayWindow::getDetailLayout();
    layout->addWidget(Producer);
    layout->addWidget(Platforms);
    
}

MultimediaDisplayWindow::~MultimediaDisplayWindow(){}
