#ifndef VIDEOGAMEEDITWINDOW_H
#define VIDEOGAMEEDITWINDOW_H


#include "MultimediaEditWindow.h"
#include "../../Model/lib/VideoGame.h"

class VideoGameEditWindow:public MultimediaEditWindow{

private:

    QTextEdit *gameEngEdit;
    QSpinBox *ExpHoursEdit;
    QTextEdit *gameTypeEdit;

    VideoGame *vgPtr;

    void setUp();

public:
    VideoGameEditWindow();
    VideoGameEditWindow(VideoGame *videogame);

public slots:
    void saveEdit() override;
};

#endif // VIDEOGAMEEDITWINDOW_H
