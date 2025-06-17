#ifndef BOOKEDITWINDOW_H
#define BOOKEDITWINDOW_H

#include "CommonEditWindow.h"
#include "../../Model/lib/Book.h"

class BookEditWindow: public CommonEditWindow{

private:
    //paper
    QTextEdit *authorEdit;
    QTextEdit *publishEdit;
    MySpinBox *pagesEdit;
    MySpinBox *volumeEdit;

    //book
    QTextEdit *mcEdit;

    //book per salvare le modifiche
    Book *bookPtr;

    void setUp();

public:
    BookEditWindow();
    BookEditWindow(Book *book);
    BookEditWindow(Content *content);

public slots:
    void saveEdit() override;
};

#endif // BOOKEDITWINDOW_H
