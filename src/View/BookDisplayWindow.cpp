#include "BookDisplayWindow.h"

BookDisplayWindow::BookDisplayWindow():
    AttributeDisplayWindow(),
    Author("", this),
    Publisher("", this),
    Pages("", this),
    Volume("", this),
    MC("", this)
{
    this->format();
}


BookDisplayWindow::BookDisplayWindow(Book *book):
    AttributeDisplayWindow(book),
    Author(QString::fromStdString(book->getAuthor()), this),
    Publisher(QString::fromStdString(book->getPublisher()), this),
    Pages(QString::number(book->getPages()), this),
    Volume(QString::number(book->getVolume()), this),
    MC(QString::fromStdString(book->getMainCharacter()), this)
{
    this->format();
}

void BookDisplayWindow::format(){
    //(Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter));
    //Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}
