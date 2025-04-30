#ifndef SERIEDISPLAYWINDOW_H
#define SERIEDISPLAYWINDOW_H

#include "VideoDisplayWindow.h"
#include "../Model/lib/Serie.h"

class SerieDisplayWindow:public VideoDisplayWindow{

private:
    QLabel Seasons;
    QLabel Episodes;
    QLabel Creator;
    QLabel Finished;

    void format();

public:
    SerieDisplayWindow();
    SerieDisplayWindow(Serie *serie);
};

#endif // SERIEDISPLAYWINDOW_H
