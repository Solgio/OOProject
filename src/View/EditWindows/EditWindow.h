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
class CommonEditWindow;

class EditWindow:public QWidget{
    Q_OBJECT

private:

    CommonEditWindow *contentEditLayout;

    QPushButton *saveButton;
    QPushButton *discardButton;

    void format();

    void buildChild(Content *contentPtr);

public slots:
    //void changeType(); //cambia il tipo del content

public:
    EditWindow(Content *content, QWidget *parent = nullptr);

};

#endif // EDITWINDOW_H
