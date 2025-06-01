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

    QFormLayout *illLayout = new QFormLayout();
    illLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Illustrator : ")), Illustrator);
    layout->addLayout(illLayout);

    QFormLayout *serieLayout = new QFormLayout();
    serieLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Serie : ")), Serie);
    layout->addLayout(serieLayout);

    QFormLayout *finLayout = new QFormLayout();
    finLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Finished : ")), Finished);
    layout->addLayout(finLayout);

    //layout->addWidget(Illustrator);
    //layout->addWidget(Serie);
    //layout->addWidget(Finished);

}

ComicDisplayWindow::~ComicDisplayWindow(){}
