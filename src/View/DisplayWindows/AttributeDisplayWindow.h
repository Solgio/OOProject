#ifndef ATTRIBUTEDISPLAYWINDOW_H
#define ATTRIBUTEDISPLAYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

class Content;
class Visitor;

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

    Visitor *view;

    QHBoxLayout *bigLayout;
    QVBoxLayout *detailLayout;

    void format();

public:
    AttributeDisplayWindow(QWidget *parent = nullptr);
    AttributeDisplayWindow(Content * content, QWidget *parent = nullptr);

    void update(Content *n_content);

    virtual QHBoxLayout* getBigLayout();
    virtual QVBoxLayout* getDetailLayout();
};

#endif // ATTRIBUTEDISPLAYWINDOW_H
