#ifndef SERIEEDITWINDOW_H
#define SERIEEDITWINDOW_H

#include "VideoEditWindow.h"
#include "../../Model/lib/Serie.h"

class SerieEditWindow:public VideoEditWindow{

private:

    QSpinBox *seasonsEdit;
    QSpinBox *episodesEdit;
    QTextEdit *creatorEdit;
    QCheckBox *finishedEdit;

    Serie *seriePtr;

    void setUp();

public:
    SerieEditWindow();
    SerieEditWindow(Serie *serie);
    SerieEditWindow(Content *content);

public slots:
    void saveEdit() override;
};

#endif // SERIEEDITWINDOW_H
