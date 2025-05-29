#include "SerieDisplayWindow.h"
#include "../../Model/lib/Serie.h"

SerieDisplayWindow::SerieDisplayWindow(Serie *serie):
    VideoDisplayWindow(serie),
    Seasons(new QLabel(QString::number(serie->getSeasons()))),
    Episodes(new QLabel(QString::number(serie->getEpisodes()))),
    Creator(new QLabel(QString::fromStdString(serie->getCreator()))),
    Finished(new QLabel(serie->getFinished() ? "Yes" : "No"))
{
    format();
}

void SerieDisplayWindow::format(){
    layout = new QVBoxLayout(this);
    layout->addWidget(Seasons);
    layout->addWidget(Episodes);
    layout->addWidget(Creator);
    layout->addWidget(Finished);
    AttributeDisplayWindow::getDetailLayout()->addLayout(layout);
}

SerieDisplayWindow::~SerieDisplayWindow(){}
