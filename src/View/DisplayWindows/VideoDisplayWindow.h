#ifndef VIDEODISPLAYWINDOW_H
#define VIDEODISPLAYWINDOW_H

#include "MultimediaDisplayWindow.h"
class Video;

class VideoDisplayWindow: public MultimediaDisplayWindow{

private:
    QLabel *Duration;
    QLabel *Prequel;
    QLabel *Sequel;
    QVBoxLayout *layout;

    void format();

public:
    VideoDisplayWindow(Video *video);
    ~VideoDisplayWindow() override;
};

#endif // VIDEODISPLAYWINDOW_H
