#ifndef VIDEOGAMEDISPLAYWINDOW_H
#define VIDEOGAMEDISPLAYWINDOW_H

#include "MultimediaDisplayWindow.h"
class VideoGame;

class VideogameDisplayWindow:public MultimediaDisplayWindow{

private:
    QLabel *GameEngine;
    QLabel *ExpectedHours;
    QLabel *GameGenre;
    QVBoxLayout *layout;

    void format();

public:
    VideogameDisplayWindow(VideoGame *videogame);
    ~VideogameDisplayWindow() override;
};

#endif // VIDEOGAMEDISPLAYWINDOW_H
