#ifndef VIDEOGAMEDISPLAYWINDOW_H
#define VIDEOGAMEDISPLAYWINDOW_H

#include "src/View/MultimediaDisplayWindow.h"
#include "../Model/lib/VideoGame.h"

class VideogameDisplayWindow:public MultimediaDisplayWindow{

private:
    QLabel GameEngine;
    QLabel ExpectedHours;
    QLabel GameGenre;

    void format();

public:
    VideogameDisplayWindow();
    VideogameDisplayWindow(VideoGame *videogame);
};

#endif // VIDEOGAMEDISPLAYWINDOW_H
