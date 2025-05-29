#include "AttributeDisplayWindow.h"
#include "../../Model/lib/Content.h"
#include "../Visitor.h"

AttributeDisplayWindow::AttributeDisplayWindow(QWidget *parent): QWidget(parent),view(new Visitor()){}


AttributeDisplayWindow::AttributeDisplayWindow(Content* content, QWidget *parent): QWidget(parent),
    Title(new QLabel(QString("<h1>%1</h1>").arg(QString::fromStdString(content->getTitle())))),
    imgString(new QString(QString::fromStdString(content->getImage()))),
    Year(new QLabel(QString::number(content->getYear()))),
    Subgenre(new QLabel(QString::fromStdString(content->getSubgenreString()))),
    Watched(new QLabel(content->getWatched() ? "Yes" : "No")),
    Starred(new QLabel(content->getStarred() ? "Yes" : "No")),
    Description(new QLabel(QString::fromStdString(content->getDescription()))),
    Type(new QLabel(QString::fromStdString(content->getType())))
{
    format();
}

void AttributeDisplayWindow::format(){

    bigLayout = new QHBoxLayout(this);

    QLabel *img = new QLabel();
    img->setPixmap(QPixmap(*imgString));

    bigLayout->addWidget(img);

    detailLayout = new QVBoxLayout();

    bigLayout->insertLayout(1, detailLayout);

    Title->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    detailLayout->addWidget(Title);
    detailLayout->addWidget(Year);
    Year->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    detailLayout->addWidget(new QLabel(QString("<h3>%1</h3>").arg("Descrizione")));
    detailLayout->addWidget(Description);
    detailLayout->addWidget(Type);

    //bigLayout->addWidget(Title);
}

QHBoxLayout* AttributeDisplayWindow::getBigLayout(){
    return bigLayout;
}
QVBoxLayout* AttributeDisplayWindow::getDetailLayout(){
    return detailLayout;
}

AttributeDisplayWindow::~AttributeDisplayWindow(){
    delete this->findChild<QLabel*>("Title");
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
