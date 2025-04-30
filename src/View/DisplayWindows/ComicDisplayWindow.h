#ifndef COMICDISPLAYWINDOW_H
#define COMICDISPLAYWINDOW_H

#include "BookDisplayWindow.h"
#include "../../Model/lib/Comic.h"

class ComicDisplayWindow: public BookDisplayWindow{

private:
    QLabel Illustrator;
    QLabel Serie;
    QLabel Finished;

    void format();

public:
    ComicDisplayWindow();
    ComicDisplayWindow(Comic *comic);
};

#endif // COMICDISPLAYWINDOW_H
