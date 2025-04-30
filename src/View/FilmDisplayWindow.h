#ifndef FILMDISPLAYWINDOW_H
#define FILMDISPLAYWINDOW_H

#include "VideoDisplayWindow.h"
#include "../Model/lib/Film.h"

class FilmDisplayWindow:public VideoDisplayWindow{

private:
    QLabel Producer;
    QLabel Photoproducer;

    void format();
public:
    FilmDisplayWindow();
    FilmDisplayWindow(Film *film);
};

#endif // FILMDISPLAYWINDOW_H
