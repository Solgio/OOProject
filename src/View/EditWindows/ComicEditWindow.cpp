#include "ComicEditWindow.h"

ComicEditWindow::ComicEditWindow():
    BookEditWindow(),
    illEdit(new QTextEdit()),
    serieEdit(new QTextEdit()),
    finishedEdit(new QCheckBox("Finished"))
{
    setUp();
}

ComicEditWindow::ComicEditWindow(Content *content):
    BookEditWindow(content),
    illEdit(new QTextEdit()),
    serieEdit(new QTextEdit()),
    finishedEdit(new QCheckBox("Finished"))
{
    setUp();
}

ComicEditWindow::ComicEditWindow(Comic *comic):
    BookEditWindow(comic),
    illEdit(new QTextEdit(QString::fromStdString(comic->getIllustrator()))),
    serieEdit(new QTextEdit(QString::fromStdString(comic->getSerie()))),
    finishedEdit(new QCheckBox("Finished")),
    comicPtr(comic)
{
    finishedEdit->setChecked(comic->getFinished());
    setUp();
}

void ComicEditWindow::setUp(){
    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Illustrator
    auto *illLayout = new QFormLayout();
    illLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Illustrator")), illEdit);
    mainLayout->addLayout(illLayout);

    //Serie
    auto *seriehLayout = new QFormLayout();
    seriehLayout->setSpacing(5);
    seriehLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Description : ")), serieEdit);
    mainLayout->addLayout(seriehLayout);

    //Finished
    auto *finLayout = new QFormLayout();
    finLayout->setSpacing(5);
    finLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Pages : ")), finishedEdit);
    mainLayout->addLayout(finLayout);

    CommonEditWindow::getTypeEditBox()->setCurrentText("Comic");
}


void ComicEditWindow::saveEdit(){
    if(comicPtr){
        BookEditWindow::saveEdit();
        comicPtr->setIllustrator(illEdit->toPlainText().QString::toStdString());
        comicPtr->setSerie(serieEdit->toPlainText().QString::toStdString());
        comicPtr->setFinished(finishedEdit->isChecked());
    }
}

