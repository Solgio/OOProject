#ifndef FILMEDITWINDOW_H
#define FILMEDITWINDOW_H

#include "VideoEditWindow.h"
#include "../../Model/lib/Film.h"

class FilmEditWindow:public VideoEditWindow{
public:
    FilmEditWindow();

public slots:
    void saveEdit() override;
};

#endif // FILMEDITWINDOW_H
