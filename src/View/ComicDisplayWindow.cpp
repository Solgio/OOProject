#include "ComicDisplayWindow.h"

ComicDisplayWindow::ComicDisplayWindow():
    BookDisplayWindow(),
    Illustrator(""),
    Serie(""),
    Finished("")
{
    this->format();
}

ComicDisplayWindow::ComicDisplayWindow(Comic *comic):
    BookDisplayWindow(comic),
    Illustrator(QString::fromStdString(comic->getIllustrator())),
    Serie(QString::fromStdString(comic->getSerie())),
    Finished(comic->getFinished() ? "Yes" : "No")
{
    this->format();
}

void ComicDisplayWindow::format(){
    //(Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter));
    //Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}
