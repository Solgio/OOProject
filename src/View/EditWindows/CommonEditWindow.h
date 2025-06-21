#ifndef COMMONEDITWINDOW_H
#define COMMONEDITWINDOW_H


#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QFormLayout>
#include <QTextEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>

class Content;
class ScienceFiction_Library;

//Creo il mio ComboBox che non riceve il segnale della rotellina del mouse
#include <QWheelEvent>
class MyComboBox: public QComboBox{
    void wheelEvent( QWheelEvent * e)
    {
        e->ignore(); //ignora l'evento della rotellina
    }
};

//Creo il mio ComboBox che non riceve il segnale della rotellina del mouse
class MySpinBox: public QSpinBox{
    void wheelEvent( QWheelEvent * e)
    {
        e->ignore(); //ignora l'evento della rotellina
    }
};

class CommonEditWindow: public QWidget{
    Q_OBJECT

private:

    ScienceFiction_Library &library;

    QTextEdit *titleEdit;

    QTextEdit *imgEdit;

    MySpinBox *yearEdit;

    QWidget *subgenreWindow;
    QList<QCheckBox*> subEdit;

    MyComboBox *inspEdit;

    QCheckBox *watchedEdit;
    QCheckBox *starredEdit;

    QTextEdit *descEdit;

    //Uso MyCheckBox che non riceve il segnale scrollWheel
    MyComboBox *typeEdit; // ! Complicato

    Content *contentPtr;

    QPushButton *searchBotton; // search bottom for image

    QPushButton *saveBotton;
    QPushButton *discardBotton;

    QHBoxLayout *bigLayout;
    QFormLayout *imgLayout;
    QVBoxLayout *detailEditLayout;

    void format();

signals:
    void contentUpdated();
    void typeUpdated(int index); //segnale emesso quando cambia il tipo

public slots:
    virtual void saveEdit();

private slots:
    void browseImage();
    void changeType(int i); //cambia il tipo del content


public:
    CommonEditWindow(QWidget *parent = nullptr);
    CommonEditWindow(Content *content, QWidget *parent = nullptr);

    QVBoxLayout* getLayout() const;
    MyComboBox* getTypeEditBox() const;

    Content* getContent() const;

};

#endif // ABSTRACTWDITWINDOW_H
