#ifndef SERIEDISPLAYWINDOW_H
#define SERIEDISPLAYWINDOW_H

#include "VideoDisplayWindow.h"
class Serie;

class SerieDisplayWindow:public VideoDisplayWindow{

private:
    QLabel *Seasons;
    QLabel *Episodes;
    QLabel *Creator;
    QLabel *Finished;
    QVBoxLayout *layout;

    void format();

public:
    SerieDisplayWindow(Serie *serie);
    ~SerieDisplayWindow() override;
};

#endif // SERIEDISPLAYWINDOW_H
