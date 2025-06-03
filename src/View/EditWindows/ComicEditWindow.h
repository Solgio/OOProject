#ifndef COMICEDITWINDOW_H
#define COMICEDITWINDOW_H

#include "BookEditWindow.h"
#include "../../Model/lib/Comic.h"

class ComicEditWindow: public BookEditWindow{

public:
    ComicEditWindow();

public slots:
    void saveEdit() override;
};

#endif // COMICEDITWINDOW_H
