#ifndef ATTRIBUTEDISPLAYWINDOW_H
#define ATTRIBUTEDISPLAYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QFormLayout>

class Content;
class ScienceFiction_Library;

class AttributeDisplayWindow: public QWidget{
    Q_OBJECT

private:
    ScienceFiction_Library &library;

    QLabel *Title;
    QString *imgString; //path in QString di image
    QLabel *Year;
    QLabel *Subgenre;
    QLabel *Watched;
    QLabel *Starred;
    QLabel *Description;
    QLabel *Type; //tipo di contenuto
    QLabel *Inspiration; //Il nome del content non il suo codice

    QHBoxLayout *bigLayout;
    QVBoxLayout *detailLayout;

    void format();

public:
    AttributeDisplayWindow(QWidget *parent = nullptr);
    AttributeDisplayWindow(Content * content, QWidget *parent = nullptr);

    virtual QVBoxLayout* getDetailLayout();

    virtual ~AttributeDisplayWindow();
};

#endif // ATTRIBUTEDISPLAYWINDOW_H
