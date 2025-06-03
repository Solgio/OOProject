#ifndef SERIEEDITWINDOW_H
#define SERIEEDITWINDOW_H

#include "VideoEditWindow.h"
#include "../../Model/lib/Serie.h"

class SerieEditWindow:public VideoEditWindow{
public:
    SerieEditWindow();

public slots:
    void saveEdit() override;
};

#endif // SERIEEDITWINDOW_H
