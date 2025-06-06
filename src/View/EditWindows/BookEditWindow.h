#ifndef BOOKEDITWINDOW_H
#define BOOKEDITWINDOW_H

#include "CommonEditWindow.h"
#include "../../Model/lib/Book.h"

class BookEditWindow: public CommonEditWindow{

private:
    //paper
    QTextEdit *authorEdit;
    QTextEdit *publishEdit;
    QSpinBox *pagesEdit;
    QSpinBox *volumeEdit;

    //book
    QTextEdit *mcEdit;

    //book per salvare le modifiche
    Book *bookPtr;

    void setUp();

public:
    BookEditWindow();
    BookEditWindow(Book *book);

public slots:
    void saveEdit() override;
};

#endif // BOOKEDITWINDOW_H
