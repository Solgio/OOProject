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

    QFormLayout *prodLayout = new QFormLayout();
    prodLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Producer : ")), Producer);
    layout->addLayout(prodLayout);

    QFormLayout *platLayout = new QFormLayout();
    platLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Platforms : ")), Platforms);
    layout->addLayout(platLayout);

    //layout->addWidget(Producer);
    //layout->addWidget(Platforms);
    
}

MultimediaDisplayWindow::~MultimediaDisplayWindow(){}
