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

class Content;

class EditWindow:public QWidget{
    Q_OBJECT

    QTextEdit *titleEdit;

    QTextEdit *imgEdit;

    QSpinBox *yearEdit;

    QList<QCheckBox*> *subEdit;

    QCheckBox *watchedEdit;

    QCheckBox *starredEdit;

    QTextEdit *descEdit;

    QComboBox *typeEdit; // ! Complicato

    QHBoxLayout *bigLayout;
    QVBoxLayout *detailLayout;

public:
    EditWindow(Content *content, QWidget *parent = nullptr);
};

#endif // EDITWINDOW_H
