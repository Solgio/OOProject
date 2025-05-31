#include "ComicDisplayWindow.h"
#include "../../Model/lib/Comic.h"

ComicDisplayWindow::ComicDisplayWindow(Comic *comic):
    BookDisplayWindow(comic),
    Illustrator(new QLabel(QString::fromStdString(comic->getIllustrator()))),
    Serie(new QLabel(QString::fromStdString(comic->getSerie()))),
    Finished(new QLabel(comic->getFinished() ? "Yes" : "No"))
{
    format();
}

void ComicDisplayWindow::format(){
    layout = AttributeDisplayWindow::getDetailLayout();
    layout->addWidget(Illustrator);
    layout->addWidget(Serie);
    layout->addWidget(Finished);

}

ComicDisplayWindow::~ComicDisplayWindow(){}
