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
    layout = AttributeDisplayWindow::getDetailLayout();

    auto *seasonLayout = new QFormLayout();
    seasonLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Seasons : ")), Seasons);
    layout->addLayout(seasonLayout);
    //layout->addWidget(Publisher);

    auto *episLayout = new QFormLayout();
    episLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Episodes : ")), Episodes);
    layout->addLayout(episLayout);
    //layout->addWidget(Pages);

    auto *creatorLayout = new QFormLayout();
    creatorLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Creator : ")), Creator);
    layout->addLayout(creatorLayout);
    //layout->addWidget(Volume);

    auto *finLayout = new QFormLayout();
    finLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Finished : ")), Finished);
    layout->addLayout(finLayout);

    //layout->addWidget(Seasons);
    //layout->addWidget(Episodes);
    //layout->addWidget(Creator);
    //layout->addWidget(Finished);
    
}

SerieDisplayWindow::~SerieDisplayWindow(){}
