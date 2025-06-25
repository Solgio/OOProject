#ifndef VIDEOEDITWINDOW_H
#define VIDEOEDITWINDOW_H

#include "MultimediaEditWindow.h"
#include "../../Model/lib/Video.h"

class VideoEditWindow:public MultimediaEditWindow{

private:
    QTextEdit *durationEdit;
    MyComboBox *prequelEdit;
    MyComboBox *sequelEdit;

    Video *videoPtr;

    void setUp();
    void setUpSequelPrequelBox();

public:
    VideoEditWindow();
    VideoEditWindow(Video *video);
    VideoEditWindow(Content *content);

    virtual void saveEdit();
};

#endif // VIDEOEDITWINDOW_H
