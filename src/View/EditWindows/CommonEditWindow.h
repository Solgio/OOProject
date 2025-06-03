#ifndef COMMONEDITWINDOW_H
#define COMMONEDITWINDOW_H

#include <QWidget>

class CommonEditWindow: public QWidget{
    Q_OBJECT

public:
    CommonEditWindow();

public slots:
    virtual void saveEdit();
};

#endif // ABSTRACTWDITWINDOW_H
