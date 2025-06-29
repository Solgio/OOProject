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

protected:
    ScienceFiction_Library &library;

private:

    QTextEdit *titleEdit;

    QTextEdit *imgEdit;
    QLabel *imageLabel;

    MySpinBox *yearEdit;

    QWidget *subgenreWindow;
    QList<QCheckBox*> subEdit;

    MyComboBox *inspEdit;

    QCheckBox *watchedEdit;
    QCheckBox *starredEdit;

    QTextEdit *descEdit;

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

public slots:
    virtual void saveEdit();

private slots:
    void browseImage();

public:
    CommonEditWindow(QWidget *parent = nullptr);
    CommonEditWindow(Content *content, QWidget *parent = nullptr);

    QVBoxLayout* getLayout() const;

    Content* getContent() const;

};

#endif // ABSTRACTWDITWINDOW_H
