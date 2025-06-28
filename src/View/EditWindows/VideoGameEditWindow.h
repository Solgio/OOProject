#ifndef VIDEOGAMEEDITWINDOW_H
#define VIDEOGAMEEDITWINDOW_H


#include "MultimediaEditWindow.h"
#include "../../Model/lib/VideoGame.h"

class VideoGameEditWindow:public MultimediaEditWindow{

private:

    QTextEdit *gameEngEdit;
    MySpinBox *ExpHoursEdit;
    MyComboBox *gameTypeEdit;

    VideoGame *vgPtr;

    void setUpGameEditBox();
    void setUp();

public:
    VideoGameEditWindow();
    VideoGameEditWindow(VideoGame *videogame);
    VideoGameEditWindow(Content *content);

public slots:
    void saveEdit() override;
};

#endif // VIDEOGAMEEDITWINDOW_H
