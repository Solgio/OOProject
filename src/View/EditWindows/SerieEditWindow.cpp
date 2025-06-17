#include "SerieEditWindow.h"

SerieEditWindow::SerieEditWindow():
    VideoEditWindow(),
    seasonsEdit(new MySpinBox()),
    episodesEdit(new MySpinBox()),
    creatorEdit(new QTextEdit()),
    finishedEdit(new QCheckBox("Finished"))
{
    setUp();
}

SerieEditWindow::SerieEditWindow(Content *content):
    VideoEditWindow(content),
    seasonsEdit(new MySpinBox()),
    episodesEdit(new MySpinBox()),
    creatorEdit(new QTextEdit()),
    finishedEdit(new QCheckBox("Finished"))
{
    setUp();
}

SerieEditWindow::SerieEditWindow(Serie *serie):
    VideoEditWindow(serie),
    seasonsEdit(new MySpinBox()),
    episodesEdit(new MySpinBox()),
    creatorEdit(new QTextEdit(QString::fromStdString(serie->getCreator()))),
    finishedEdit(new QCheckBox("Finished")),
    seriePtr(serie)
{
    seasonsEdit->setValue(serie->getSeasons());
    episodesEdit->setValue(serie->getEpisodes());
    finishedEdit->setChecked(serie->getFinished());

    setUp();
}

void SerieEditWindow::setUp(){
    QVBoxLayout *mainLayout = CommonEditWindow::getLayout();

    //Seasons
    auto *seasonsLayout = new QFormLayout();
    seasonsLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Seasons : ")), seasonsEdit);
    mainLayout->addLayout(seasonsLayout);

    //Episodes
    auto *episodesLayout = new QFormLayout();
    episodesLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Episodes : ")), episodesEdit);
    mainLayout->addLayout(episodesLayout);

    //Creator
    auto *creatorLayout = new QFormLayout();
    creatorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Creator : ")), creatorEdit);
    mainLayout->addLayout(creatorLayout);

    //Finished
    auto *finishedLayout = new QFormLayout();
    finishedLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Finished : ")), finishedEdit);
    mainLayout->addLayout(finishedLayout);

    CommonEditWindow::getTypeEditBox()->setCurrentText("Serie");
}

void SerieEditWindow::saveEdit(){
    if(seriePtr){
        VideoEditWindow::saveEdit();
        seriePtr->setSeasons(seasonsEdit->value());
        seriePtr->setEpisodes(episodesEdit->value());
        seriePtr->setCreator(creatorEdit->toPlainText().QString::toStdString());
        seriePtr->setFinished(finishedEdit->isChecked());
    }
}
