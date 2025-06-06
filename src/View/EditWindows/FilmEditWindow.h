#ifndef FILMEDITWINDOW_H
#define FILMEDITWINDOW_H

#include "VideoEditWindow.h"
#include "../../Model/lib/Film.h"

class FilmEditWindow:public VideoEditWindow{

private:
    QTextEdit *dirEdit;
    QTextEdit *photoDirEdit;

    Film *filmPtr;
public:
    FilmEditWindow();
    FilmEditWindow(Film *film);

    void setUp();

public slots:
    void saveEdit() override;
};

#endif // FILMEDITWINDOW_H
