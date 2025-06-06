#include "SerieEditWindow.h"

SerieEditWindow::SerieEditWindow():
    VideoEditWindow(serie),
    seasonsEdit(new QSpinBox()),
    episodesEdit(new QSpinBox()),
    creatorEdit(new QTextEdit()),
    finishedEdit(new QCheckBox("Finished"))
{
    setUp();
}

SerieEditWindow::SerieEditWindow(Serie *serie):
    VideoEditWindow(serie),
    seasonsEdit(new QSpinBox()),
    episodesEdit(new QSpinBox()),
    creatorEdit(new QTextEdit(QString::fromStdString(serie->getCreator()))),
    finishedEdit(new QCheckBox("Finished")),
    seriePtr(serie)
{
    seasonsEdit->setValue(serie->getSeasons());
    episodesEdit->setValue(serie->getEpisodes());
    finishedEdit->setTristate(serie->getFinished());

    setUp();
}

void SerieEditWindow::setUp(){
    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Seasons
    QFormLayout *seasonsLayout = new QFormLayout();
    seasonsLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Seasons : ")), seasonsEdit);
    mainLayout->addLayout(seasonsLayout);

    //Episodes
    QFormLayout *episodesLayout = new QFormLayout();
    episodesLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Episodes : ")), episodesEdit);
    mainLayout->addLayout(episodesLayout);

    //Creator
    QFormLayout *creatorLayout = new QFormLayout();
    creatorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Creator : ")), creatorEdit);
    mainLayout->addLayout(creatorLayout);

    //Finished
    QFormLayout *finishedLayout = new QFormLayout();
    finishedLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Finished : ")), finishedEdit);
    mainLayout->addLayout(finishedLayout);
}

void SerieEditWindow::saveEdit(){
    if(seriePtr){
        VideoEditWindow::saveEdit();
        seriePtr->setSeasons(seasonsEdit->value());
        seriePtr->setEpisodes(episodesEdit->value());
        seriePtr->setCreator(creatorEdit->toPlainText().QString::toStdString());
        seriePtr->setFinished(finishedEdit->isTristate());
    }
}
