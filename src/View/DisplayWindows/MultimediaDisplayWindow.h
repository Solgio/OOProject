#ifndef MULTIMEDIADISPLAYWINDOW_H
#define MULTIMEDIADISPLAYWINDOW_H

#include "AttributeDisplayWindow.h"
#include "../../Model/lib/Multimedia.h"

class MultimediaDisplayWindow: public AttributeDisplayWindow{

private:
    QLabel Producer;
    QLabel Platforms;

    void format();

public:
    MultimediaDisplayWindow();
    MultimediaDisplayWindow(Multimedia *multm);
};

#endif // MULTIMEDIADISPLAYWINDOW_H
