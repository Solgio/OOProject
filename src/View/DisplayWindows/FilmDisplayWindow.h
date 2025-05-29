#ifndef FILMDISPLAYWINDOW_H
#define FILMDISPLAYWINDOW_H

#include "VideoDisplayWindow.h"
class Film;

class FilmDisplayWindow:public VideoDisplayWindow{

private:
    QLabel *Producer;
    QLabel *Photoproducer;
    QVBoxLayout *layout;

    void format();
public:
    FilmDisplayWindow(Film *film);
    ~FilmDisplayWindow() override;
};

#endif // FILMDISPLAYWINDOW_H
