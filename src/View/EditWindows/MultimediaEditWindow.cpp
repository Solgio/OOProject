#include "MultimediaEditWindow.h"

MultimediaEditWindow::MultimediaEditWindow():
    CommonEditWindow(),
    prodEdit(new QTextEdit()),
    platEdit(new QTextEdit())
{
    setUp();
}

MultimediaEditWindow::MultimediaEditWindow(Content *content):
    CommonEditWindow(content),
    prodEdit(new QTextEdit()),
    platEdit(new QTextEdit())
{
    setUp();
}

MultimediaEditWindow::MultimediaEditWindow(Multimedia *mult):
    CommonEditWindow(mult),
    prodEdit(new QTextEdit(QString::fromStdString(mult->getProducer()))),
    platEdit(new QTextEdit(QString::fromStdString(mult->getPlatforms()))),
    multPtr(mult)
{
    setUp();
}

void MultimediaEditWindow::setUp(){
    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Producer
    QFormLayout *prodLayout = new QFormLayout();
    prodLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Producer : ")), prodEdit);
    mainLayout->addLayout(prodLayout);

    //Platforms
    QFormLayout *platLayout = new QFormLayout();
    platLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Platforms : ")), platEdit);
    mainLayout->addLayout(platLayout);
}

void MultimediaEditWindow::saveEdit(){
    if(multPtr){
        CommonEditWindow::saveEdit();
        multPtr->setProducer(prodEdit->toPlainText().QString::toStdString());
        multPtr->setPlatforms(platEdit->toPlainText().QString::toStdString());
    }
}
