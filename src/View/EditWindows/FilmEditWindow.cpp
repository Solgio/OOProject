#include "FilmEditWindow.h"

FilmEditWindow::FilmEditWindow():
    VideoEditWindow(),
    dirEdit(new QTextEdit()),
    photoDirEdit(new QTextEdit())
{
    setUp();
}

FilmEditWindow::FilmEditWindow(Film *film):
    VideoEditWindow(film),
    dirEdit(new QTextEdit(QString::fromStdString(film->getDirector()))),
    photoDirEdit(new QTextEdit(QString::fromStdString(film->getPhotoDirector()))),
    filmPtr(film)
{
    setUp();
}

void FilmEditWindow::setUp(){
    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Director
    QFormLayout *dirLayout = new QFormLayout();
    dirLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Director : ")), dirEdit);
    mainLayout->addLayout(dirLayout);

    //Photodirector
    QFormLayout *photoDirLayout = new QFormLayout();
    photoDirLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Photodirector : ")), photoDirEdit);
    mainLayout->addLayout(photoDirLayout);
}

void FilmEditWindow::saveEdit(){
    if(filmPtr){
        VideoEditWindow::saveEdit();
        filmPtr->setDirector(dirEdit->toPlainText().QString::toStdString());
        filmPtr->setPhotoDirector(photoDirEdit->toPlainText().QString::toStdString());
    }
}
