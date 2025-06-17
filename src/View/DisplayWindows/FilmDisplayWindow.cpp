#include "FilmDisplayWindow.h"
#include "../../Model/lib/Film.h"

FilmDisplayWindow::FilmDisplayWindow(Film *film):
    VideoDisplayWindow(film),
    Director(new QLabel(QString::fromStdString(film->getDirector()))),
    Photoproducer(new QLabel(QString::fromStdString(film->getPhotoDirector())))
{
    format();
}

void FilmDisplayWindow::format(){
    layout = AttributeDisplayWindow::getDetailLayout();

    auto *direcLayout = new QFormLayout();
    direcLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Director : ")), Director);
    layout->addLayout(direcLayout);

    auto *photoLayout = new QFormLayout();
    photoLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Photoproducer : ")), Photoproducer);
    layout->addLayout(photoLayout);

    //layout->addWidget(Producer);
    //layout->addWidget(Photoproducer);
    
}

FilmDisplayWindow::~FilmDisplayWindow(){}
