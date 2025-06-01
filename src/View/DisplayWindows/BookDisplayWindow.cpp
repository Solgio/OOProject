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
    layout = AttributeDisplayWindow::getDetailLayout();

    QFormLayout *authorLayout = new QFormLayout();
    authorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Author : ")), Author);
    /*authorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Publisher : ")), Publisher);
    authorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Pages : ")), Pages);
    authorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Volume : ")), Volume);
    authorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Main Character : ")), MC);*/
    layout->addLayout(authorLayout);
    //layout->addWidget(Author);

    QFormLayout *PupLayout = new QFormLayout();
    PupLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Publisher : ")), Publisher);
    layout->addLayout(PupLayout);
    //layout->addWidget(Publisher);

    QFormLayout *pagesLayout = new QFormLayout();
    pagesLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Pages : ")), Pages);
    layout->addLayout(pagesLayout);
    //layout->addWidget(Pages);

    QFormLayout *volumeLayout = new QFormLayout();
    volumeLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Volume : ")), Volume);
    layout->addLayout(volumeLayout);
    //layout->addWidget(Volume);

    QFormLayout *mcLayout = new QFormLayout();
    mcLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Main Character : ")), MC);
    layout->addLayout(mcLayout);
    //layout->addWidget(MC);

}

BookDisplayWindow::~BookDisplayWindow(){}
