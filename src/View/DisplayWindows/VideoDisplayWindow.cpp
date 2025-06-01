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

    QFormLayout *durLayout = new QFormLayout();
    durLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Duration : ")), Duration);
    layout->addLayout(durLayout);
    //layout->addWidget(Pages);

    QFormLayout *preLayout = new QFormLayout();
    preLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Prequel : ")), Prequel);
    layout->addLayout(preLayout);
    //layout->addWidget(Volume);

    QFormLayout *seqLayout = new QFormLayout();
    seqLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Sequel : ")), Sequel);
    layout->addLayout(seqLayout);

    //layout->addWidget(Duration);
    //layout->addWidget(Prequel);
    //layout->addWidget(Sequel);
    
}

VideoDisplayWindow::~VideoDisplayWindow(){}
