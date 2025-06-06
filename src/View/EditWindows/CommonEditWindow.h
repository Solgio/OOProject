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
class CommonEditWindow;

//L'oggetto ha solo il compito di contenere la funzione virtuale saveEdit() ed essere il genitore dei classi ___EditWindow eccetto EditWindow.cpp/.h

class CommonEditWindow: public QWidget{
    Q_OBJECT

private:

    QTextEdit *titleEdit;

    QTextEdit *imgEdit;

    QSpinBox *yearEdit;

    QWidget *subgenreWindow;
    QList<QCheckBox*> subEdit;

    QCheckBox *watchedEdit;

    QCheckBox *starredEdit;

    QTextEdit *descEdit;

    QComboBox *typeEdit; // ! Complicato

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

    void changeType(); //cambia il tipo del content


public:
    CommonEditWindow(QWidget *parent = nullptr);
    CommonEditWindow(Content *content, QWidget *parent = nullptr);
    QVBoxLayout* getLayout();



};

#endif // ABSTRACTWDITWINDOW_H
