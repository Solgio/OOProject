#ifndef COMICDISPLAYWINDOW_H
#define COMICDISPLAYWINDOW_H

#include "BookDisplayWindow.h"
class Comic;

class ComicDisplayWindow: public BookDisplayWindow{

private:
    QLabel *Illustrator;
    QLabel *Serie;
    QLabel *Finished;
    QVBoxLayout *layout;

    void format();

public:
    ComicDisplayWindow(Comic *comic);
};

#endif // COMICDISPLAYWINDOW_H
