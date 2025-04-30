#ifndef BOOKDISPLAYWINDOW_H
#define BOOKDISPLAYWINDOW_H

#include "AttributeDisplayWindow.h"
#include "../Model/lib/Book.h"

class BookDisplayWindow: public AttributeDisplayWindow{

private:
    //Paper
    QLabel Author;
    QLabel Publisher;
    QLabel Pages;
    QLabel Volume;

    //Book
    QLabel MC;

    void format();

public:
    BookDisplayWindow();
    BookDisplayWindow(Book *book);
};

#endif // BOOKDISPLAYWINDOW_H
