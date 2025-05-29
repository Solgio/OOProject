#include "BookDisplayWindow.h"
#include "../../Model/lib/Book.h"



BookDisplayWindow::BookDisplayWindow(Book *book):
    AttributeDisplayWindow(book),
    Author(new QLabel(QString::fromStdString(book->getAuthor()))),
    Publisher(new QLabel((QString::fromStdString(book->getPublisher())))),
    Pages(new QLabel(QString::number(book->getPages()))),
    Volume(new QLabel(QString::number(book->getVolume()))),
    MC(new QLabel(QString::fromStdString(book->getMainCharacter())))
{
    format();
}

void BookDisplayWindow::format(){
    layout = new QVBoxLayout();
    layout->addWidget(Author);
    layout->addWidget(Publisher);
    layout->addWidget(Pages);
    layout->addWidget(Volume);
    layout->addWidget(MC);
    AttributeDisplayWindow::getDetailLayout()->addLayout(layout);
}

BookDisplayWindow::~BookDisplayWindow(){}
