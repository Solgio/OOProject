#ifndef VIDEOEDITWINDOW_H
#define VIDEOEDITWINDOW_H

#include "MultimediaEditWindow.h"
#include "../../Model/lib/Video.h"

class VideoEditWindow:public MultimediaEditWindow{

private:
    QTextEdit *durationEdit;
    QTextEdit *prequelEdit;
    QTextEdit *sequelEdit;

    Video *videoPtr;

    void setUp();

public:
    VideoEditWindow();
    VideoEditWindow(Video *video);

    virtual void saveEdit();
};

#endif // VIDEOEDITWINDOW_H
