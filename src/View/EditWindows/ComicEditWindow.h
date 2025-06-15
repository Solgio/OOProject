#ifndef COMICEDITWINDOW_H
#define COMICEDITWINDOW_H

#include "BookEditWindow.h"
#include "../../Model/lib/Comic.h"

class ComicEditWindow: public BookEditWindow{

private:
    //comic
    QTextEdit *illEdit;
    QTextEdit *serieEdit;
    QCheckBox *finishedEdit;

    //per salvare le modifiche
    Comic *comicPtr;

    void setUp();
public:
    ComicEditWindow();
    ComicEditWindow(Comic * comic);
    ComicEditWindow(Content *content);

public slots:
    void saveEdit() override;
};

#endif // COMICEDITWINDOW_H
