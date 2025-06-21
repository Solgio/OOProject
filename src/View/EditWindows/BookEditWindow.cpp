#include "BookEditWindow.h"

BookEditWindow::BookEditWindow():
    CommonEditWindow(),
    authorEdit(new QTextEdit()),
    publishEdit(new QTextEdit()),
    pagesEdit(new MySpinBox()),
    volumeEdit(new MySpinBox()),
    mcEdit(new QTextEdit())
{
    pagesEdit->setRange(0,1000);
    volumeEdit->setRange(0,1000);

    setUp();
}

BookEditWindow::BookEditWindow(Content *content):
    CommonEditWindow(content),
    authorEdit(new QTextEdit()),
    publishEdit(new QTextEdit()),
    pagesEdit(new MySpinBox()),
    volumeEdit(new MySpinBox()),
    mcEdit(new QTextEdit())
{
    pagesEdit->setRange(0,1000);
    volumeEdit->setRange(0,1000);

    setUp();
}

BookEditWindow::BookEditWindow(Book *book):
    CommonEditWindow(book),
    authorEdit(new QTextEdit(QString::fromStdString(book->getAuthor()))),
    publishEdit(new QTextEdit(QString::fromStdString(book->getPublisher()))),
    pagesEdit(new MySpinBox()),
    volumeEdit(new MySpinBox()),
    mcEdit(new QTextEdit(QString::fromStdString(book->getMainCharacter()))),
    bookPtr(book)
{
    pagesEdit->setRange(0,1000);
    volumeEdit->setRange(0,1000);
    pagesEdit->setValue(book->getPages());
    volumeEdit->setValue(book->getVolume());

    setUp();

}

void BookEditWindow::setUp(){

    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Author
    auto *authorLayout = new QFormLayout();
    authorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Author : ")), authorEdit);
    mainLayout->addLayout(authorLayout);

    //Publisher
    auto *publishLayout = new QFormLayout();
    publishLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Description : ")), publishEdit);
    mainLayout->addLayout(publishLayout);

    //Pages
    auto *pagesLayout = new QFormLayout();
    pagesLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Pages : ")), pagesEdit);
    mainLayout->addLayout(pagesLayout);

    //Volume
    auto *volumeLayout = new QFormLayout();
    volumeLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Volume : ")), volumeEdit);
    mainLayout->addLayout(volumeLayout);

    //Main Character
    auto *mcLayout = new QFormLayout();
    mcLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Main Character : ")), mcEdit);
    mainLayout->addLayout(mcLayout);

    CommonEditWindow::getTypeEditBox()->setCurrentText("Book");

}

void BookEditWindow::saveEdit(){ //speriamo che funzioni
    if(bookPtr){
        CommonEditWindow::saveEdit();
        bookPtr->setAuthor(authorEdit->toPlainText().QString::toStdString());
        bookPtr->setPublisher(publishEdit->toPlainText().QString::toStdString());
        bookPtr->setPages(pagesEdit->value());
        bookPtr->setVolume(volumeEdit->value());
        bookPtr->setMainCharacter(mcEdit->toPlainText().QString::toStdString());
    }
}
