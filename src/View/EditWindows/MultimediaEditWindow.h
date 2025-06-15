#ifndef MULTIMEDIAEDITWINDOW_H
#define MULTIMEDIAEDITWINDOW_H

#include "CommonEditWindow.h"
#include "../../Model/lib/Multimedia.h"

class MultimediaEditWindow:public CommonEditWindow{

private:

    QTextEdit *prodEdit;
    QTextEdit *platEdit;

    Multimedia *multPtr;

    void setUp();

public:
    MultimediaEditWindow();
    MultimediaEditWindow(Multimedia *mult);
    MultimediaEditWindow(Content *content);

    virtual void saveEdit();
};

#endif // MULTIMEDIAEDITWINDOW_H
