#ifndef BOOKDISPLAYWINDOW_H
#define BOOKDISPLAYWINDOW_H
#include "AttributeDisplayWindow.h"

class Book;

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
