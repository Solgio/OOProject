#ifndef BOOKEDITWINDOW_H
#define BOOKEDITWINDOW_H

#include "CommonEditWindow.h"
#include "../../Model/lib/Book.h"

class BookEditWindow: public CommonEditWindow{

public:
    BookEditWindow();

public slots:
    void saveEdit() override;
};

#endif // BOOKEDITWINDOW_H
