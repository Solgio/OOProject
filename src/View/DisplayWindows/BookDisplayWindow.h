#ifndef BOOKDISPLAYWINDOW_H
#define BOOKDISPLAYWINDOW_H
#include "AttributeDisplayWindow.h"

class Book;

class BookDisplayWindow: public AttributeDisplayWindow{

private:
    //Paper
    QLabel *Author;
    QLabel *Publisher;
    QLabel *Pages;
    QLabel *Volume;

    //Book
    QLabel *MC;

    QVBoxLayout *layout;

    void format();

public:
    BookDisplayWindow(Book *book);
    //void update(Book *book) override;
};

#endif // BOOKDISPLAYWINDOW_H
