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
    layout = new QVBoxLayout(this);
    layout->addWidget(Producer);
    layout->addWidget(Platforms);
    AttributeDisplayWindow::getDetailLayout()->addLayout(layout);
}

MultimediaDisplayWindow::~MultimediaDisplayWindow(){}
