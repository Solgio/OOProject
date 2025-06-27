#include "VideoDisplayWindow.h"
#include "../../Model/lib/Video.h"
#include "../../Model/lib/ScienceFictionLibrary.h"

VideoDisplayWindow::VideoDisplayWindow(Video *video):
    MultimediaDisplayWindow(video),
    Duration(new QLabel(QString::number(video->getDuration())))
{
    if(const Content* tempPre = AttributeDisplayWindow::library.searchId(video->getPrequel()); tempPre){
        Prequel = new QLabel(QString::fromStdString(tempPre->getTitle()));
    }else{
        Prequel = new QLabel("No Prequel");
    }

    if(const Content* tempSeq = AttributeDisplayWindow::library.searchId(video->getSequel()); tempSeq){
        Sequel = new QLabel(QString::fromStdString(tempSeq->getTitle()));
    }else{
        Sequel = new QLabel("No Prequel");
    }
    format();
}

void VideoDisplayWindow::format(){
    layout = AttributeDisplayWindow::getDetailLayout();

    auto *durLayout = new QFormLayout();
    durLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Duration : ")), Duration);
    layout->addLayout(durLayout);
    //layout->addWidget(Pages);

    auto *preLayout = new QFormLayout();
    preLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Prequel : ")), Prequel);
    layout->addLayout(preLayout);
    //layout->addWidget(Volume);

    auto *seqLayout = new QFormLayout();
    seqLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Sequel : ")), Sequel);
    layout->addLayout(seqLayout);

    //layout->addWidget(Duration);
    //layout->addWidget(Prequel);
    //layout->addWidget(Sequel);
    
}

VideoDisplayWindow::~VideoDisplayWindow(){}
