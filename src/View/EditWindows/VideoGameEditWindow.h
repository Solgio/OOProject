#ifndef VIDEOGAMEEDITWINDOW_H
#define VIDEOGAMEEDITWINDOW_H


#include "MultimediaEditWindow.h"
#include "../../Model/lib/VideoGame.h"

class VideoGameEditWindow:public MultimediaEditWindow{
public:
    VideoGameEditWindow();

public slots:
    void saveEdit() override;
};

#endif // VIDEOGAMEEDITWINDOW_H
