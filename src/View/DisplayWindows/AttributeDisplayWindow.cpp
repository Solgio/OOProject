#include "AttributeDisplayWindow.h"

AttributeDisplayWindow::AttributeDisplayWindow(QWidget *parent): QWidget(parent),
    Title("", this),
    Year("", this),
    Subgenre("", this),
    Watched("False", this),
    Starred("False", this),
    Description("", this),
    Type("", this)
{
    format();
}


AttributeDisplayWindow::AttributeDisplayWindow(Content* content, QWidget *parent): QWidget(parent),
    Title(QString("<h1>%1</h1>").arg(QString::fromStdString(content->getTitle())), this),
    Year(QString::number(content->getYear()), this),
    Subgenre(QString::fromStdString(content->getSubgenreString()), this),
    Watched(content->getWatched() ? "Yes" : "No", this),
    Starred(content->getStarred() ? "Yes" : "No", this),
    Description(QString::fromStdString(content->getDescription()), this),
    Type(QString::fromStdString(content->getType()), this)
{
    format();
}

void AttributeDisplayWindow::format(){
    (Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter));
    Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}
/*
 *QString("<div style='margin:10px;'>").arg()
 *
        "<div style='margin:10px;'>"
        "<h2>%1</h2>"
        "<div style='float:right; margin-left:20px;'>"
        "<img src='%2' width='200' onerror=\"this.src=':assets/icons/default.png'\">"
        "</div>"
        "<p><b>Type:</b> %8</p>"
        "<p><b>Year:</b> %3</p>"
        "<p><b>Genre:</b> %4</p>"
        "<p><b>Watched:</b> %5</p>"
        "<p><b>Starred:</b> %6</p>"
        "<p><b>Description:</b><br>%7</p>"
        "</div>"
 *
 *
        QString::fromStdString(content->getTitle()),
        QString::fromStdString(content->getImage()),
        QString::number(content->getYear()),
        QString::fromStdString(content->getSubgenreString()),
        content->getWatched() ? "Yes" : "No",
        content->getStarred() ? "Yes" : "No",
        QString::fromStdString(content->getDescription()),
        QString::fromStdString(content->getType())
*/
