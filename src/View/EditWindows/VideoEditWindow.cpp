#include "VideoEditWindow.h"

VideoEditWindow::VideoEditWindow():
    MultimediaEditWindow(),
    durationEdit(new QTextEdit()),
    prequelEdit(new QTextEdit()),
    sequelEdit(new QTextEdit())
{
    setUp();
}

VideoEditWindow::VideoEditWindow(Content *content):
    MultimediaEditWindow(content),
    durationEdit(new QTextEdit()),
    prequelEdit(new QTextEdit()),
    sequelEdit(new QTextEdit())
{
    setUp();
}


VideoEditWindow::VideoEditWindow(Video *video):
    MultimediaEditWindow(video),
    durationEdit(new QTextEdit(QString::number(video->getDuration()))),
    prequelEdit(new QTextEdit(QString::number(video->getPrequel()))),
    sequelEdit(new QTextEdit(QString::number(video->getSequel()))),
    videoPtr(video)
{
    setUp();
}

void VideoEditWindow::setUp(){
    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Duration
    QFormLayout *durationLayout = new QFormLayout();
    durationLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Duration (in minutes) : ")), durationEdit);
    mainLayout->addLayout(durationLayout);

    //Prequel ID
    QFormLayout *preqLayout = new QFormLayout();
    preqLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Prequel ID : ")), prequelEdit);
    mainLayout->addLayout(preqLayout);

    //Sequel ID
    QFormLayout *seqLayout = new QFormLayout();
    seqLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Sequel ID : ")), sequelEdit);
    mainLayout->addLayout(seqLayout);
}

void VideoEditWindow::saveEdit(){
    if(videoPtr){
        MultimediaEditWindow::saveEdit();
        videoPtr->setDuration(durationEdit->toPlainText().toUInt());
        videoPtr->setPrequel(prequelEdit->toPlainText().toUInt());
        videoPtr->setSequel(sequelEdit->toPlainText().toUInt());
    }
}
