#include "FilmDisplayWindow.h"
#include "../../Model/lib/Film.h"

FilmDisplayWindow::FilmDisplayWindow(Film *film):
    VideoDisplayWindow(film),
    Producer(new QLabel(QString::fromStdString(film->getProducer()))),
    Photoproducer(new QLabel(QString::fromStdString(film->getPhotoDirector())))
{
    format();
}

void FilmDisplayWindow::format(){
    layout = new QVBoxLayout(this);
    layout->addWidget(Producer);
    layout->addWidget(Photoproducer);
    AttributeDisplayWindow::getDetailLayout()->addLayout(layout);
}

FilmDisplayWindow::~FilmDisplayWindow(){}
