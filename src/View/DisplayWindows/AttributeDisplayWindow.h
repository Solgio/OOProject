#ifndef ATTRIBUTEDISPLAYWINDOW_H
#define ATTRIBUTEDISPLAYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QFormLayout>

class Content;

class AttributeDisplayWindow: public QWidget{
    Q_OBJECT

private:
    QLabel *Title;
    QString *imgString; //path in QString di image
    QLabel *Year;
    QLabel *Subgenre;
    QLabel *Watched;
    QLabel *Starred;
    QLabel *Description;
    QLabel *Type; //tipo di contenuto

    QHBoxLayout *bigLayout;
    QVBoxLayout *detailLayout;

    void format();

public:
    AttributeDisplayWindow(QWidget *parent = nullptr);
    AttributeDisplayWindow(Content * content, QWidget *parent = nullptr);

    virtual QHBoxLayout* getBigLayout();
    virtual QVBoxLayout* getDetailLayout();

    virtual ~AttributeDisplayWindow();
};

#endif // ATTRIBUTEDISPLAYWINDOW_H
