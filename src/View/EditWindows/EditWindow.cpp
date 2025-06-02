#include "EditWindow.h"
#include "../../Model/lib/Content.h"

EditWindow::EditWindow(Content *content, QWidget *parent): QWidget(parent),
    titleEdit(new QTextEdit(QString::fromStdString(content->getTitle()))),
    imgEdit(new QTextEdit(QString::fromStdString(content->getImage()))),
    yearEdit(new QSpinBox()),
    watchedEdit(new QCheckBox(content->getWatched() ? "Yes" : "No")),
    starredEdit(new QCheckBox(content->getStarred() ? "Yes" : "No")),
    descEdit(new QTextEdit(QString::fromStdString(content->getDescription())))
{}
