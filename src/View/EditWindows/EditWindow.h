#ifndef EDITWINDOW_H
#define EDITWINDOW_H

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

class EditWindow:public QWidget{
    Q_OBJECT

    QTextEdit *titleEdit;

    QTextEdit *imgEdit;

    QSpinBox *yearEdit;

    QWidget *subgenreWindow;
    QList<QCheckBox*> subEdit;

    QCheckBox *watchedEdit;

    QCheckBox *starredEdit;

    QTextEdit *descEdit;

    QComboBox *typeEdit; // ! Complicato

    QPushButton *searchBotton; // search bottom for image

    QPushButton *saveBotton;
    QPushButton *discardBotton;

    QHBoxLayout *bigLayout;
    QFormLayout *imgLayout;
    QVBoxLayout *detailEditLayout;

    QVBoxLayout *childrenEditLayout;

    void format();

private slots:
    void saveChanges();
    void browseImage();

    void changeType(); //cambia childrenEditLayout al figlio giusto

public:

    EditWindow(Content *content, QWidget *parent = nullptr);

};

#endif // EDITWINDOW_H
