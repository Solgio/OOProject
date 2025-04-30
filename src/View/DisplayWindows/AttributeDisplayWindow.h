#ifndef ATTRIBUTEDISPLAYWINDOW_H
#define ATTRIBUTEDISPLAYWINDOW_H

#include <QWidget>
#include <QLabel>
#include "../../Model/lib/Content.h"
//#include "ContentDetailWindow.h"

class AttributeDisplayWindow: public QWidget{
    Q_OBJECT

private:
    QLabel Title;
    //NO image
    QLabel Year;
    QLabel Subgenre;
    QLabel Watched;
    QLabel Starred;
    QLabel Description;
    QLabel Type; //tipo di contenuto

    void format();

public:
    AttributeDisplayWindow(QWidget *parent = nullptr);
    AttributeDisplayWindow(Content * content, QWidget *parent = nullptr);

    virtual ~AttributeDisplayWindow() = default;
};

#endif // ATTRIBUTEDISPLAYWINDOW_H
