#include "AttributeDisplayWindow.h"
#include "../../Model/lib/Content.h"

AttributeDisplayWindow::AttributeDisplayWindow(QWidget *parent): QWidget(parent){};

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

    bigLayout = new QHBoxLayout(this); //Box orizzontale che contiene a sinistra l'immagine e destra gli dettagli del content

    QLabel *img = new QLabel();

    if (!imgString->isEmpty() && QFile::exists(*imgString)) {
        img->setPixmap(QPixmap(*imgString).scaled(500,500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        img->setAlignment(Qt::AlignCenter);
    } else {
        img->setPixmap(QPixmap(":assets/icons/no-image.png").scaled(500,500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    img->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    bigLayout->addWidget(img); //aggiunta dell'immagine per occupare il lato sinistro

    detailLayout = new QVBoxLayout(); //Box verticale per gli dettagli del content

    detailLayout->setSpacing(15);
    //detailLayout->setContentsMargins(5, 5, 5, 5);

    detailLayout->setAlignment(Qt::AlignTop);
    //detailLayout->insertSpacing(-1, 10); //aggiunge un spacer alla fine del layout per portare compattare i campi

    bigLayout->insertLayout(1, detailLayout);

    //Ogni campo ha un suo layout

    QFormLayout *titleLayout = new QFormLayout();
    Title->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    Year->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    titleLayout->addRow(Title);
    titleLayout->addRow(Year);
    //detailLayout->addWidget(Title);
    //detailLayout->addWidget(Year);
    detailLayout->addLayout(titleLayout);

    QFormLayout *descrLayout = new QFormLayout();
    descrLayout->setSpacing(5); //riduce lo spazio tra "Description :" e la descrizione
    descrLayout->addRow(new QLabel(QString("<h2>%1</h2>").arg("Description : ")));
    descrLayout->addRow(Description);
    //descrLayout->addItem(new QSpacerItem(0, 20));
    //descrLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Type : ")), Type);
    detailLayout->addLayout(descrLayout);

    //separatore tra i layout


    QFormLayout *typeLayout = new QFormLayout();
    typeLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Type : ")), Type);
    detailLayout->addLayout(typeLayout);

    //detailLayout->addWidget(new QLabel(QString("<h3>%1</h3>").arg("Descrizione")));
    //detailLayout->addWidget(Description);
    //detailLayout->addWidget(Type);

    //bigLayout->addWidget(Title);
    //detailLayout->addStretch(200);
}

QHBoxLayout* AttributeDisplayWindow::getBigLayout(){
    return bigLayout;
}
QVBoxLayout* AttributeDisplayWindow::getDetailLayout(){
    return detailLayout;
}

AttributeDisplayWindow::~AttributeDisplayWindow(){
}

