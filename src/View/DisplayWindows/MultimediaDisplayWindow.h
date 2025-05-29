#ifndef MULTIMEDIADISPLAYWINDOW_H
#define MULTIMEDIADISPLAYWINDOW_H

#include "AttributeDisplayWindow.h"
class Multimedia;

class MultimediaDisplayWindow: public AttributeDisplayWindow{

private:
    QLabel *Producer;
    QLabel *Platforms;
    QVBoxLayout *layout;

    void format();

public:
    MultimediaDisplayWindow(Multimedia *multm);
    ~MultimediaDisplayWindow() override;
};

#endif // MULTIMEDIADISPLAYWINDOW_H
