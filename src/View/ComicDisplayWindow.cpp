#include "ComicDisplayWindow.h"

ComicDisplayWindow::ComicDisplayWindow():
    BookDisplayWindow(),
    Illustrator("", this),
    Serie("", this),
    Finished("", this)
{
    this->format();
}

ComicDisplayWindow::ComicDisplayWindow(Comic *comic):
    BookDisplayWindow(comic),
    Illustrator(QString::fromStdString(comic->getIllustrator()), this),
    Serie(QString::fromStdString(comic->getSerie()), this),
    Finished(comic->getFinished() ? "Yes" : "No", this)
{
    this->format();
}

void ComicDisplayWindow::format(){
    //(Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter));
    //Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}
