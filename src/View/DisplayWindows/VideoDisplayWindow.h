#ifndef VIDEODISPLAYWINDOW_H
#define VIDEODISPLAYWINDOW_H

#include "MultimediaDisplayWindow.h"
#include "../../Model/lib/Video.h"

class VideoDisplayWindow: public MultimediaDisplayWindow{

private:
    QLabel Duration;
    QLabel Prequel;
    QLabel Sequel;

    void format();

public:
    VideoDisplayWindow();
    VideoDisplayWindow(Video *video);
};

#endif // VIDEODISPLAYWINDOW_H
