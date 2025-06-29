#include "AttributeDisplayWindow.h"
#include "../../Model/lib/Content.h"
#include "../../Model/lib/ScienceFictionLibrary.h"

AttributeDisplayWindow::AttributeDisplayWindow(QWidget *parent): QWidget(parent),
    library(ScienceFiction_Library::getInstance()){};

AttributeDisplayWindow::AttributeDisplayWindow(Content* content, QWidget *parent): QWidget(parent),
    library(ScienceFiction_Library::getInstance()),
    Title(new QLabel(QString("<h1>%1</h1>").arg(QString::fromStdString(content->getTitle())))),
    imgString(new QString(QString::fromStdString(content->getImage()))),
    Year(new QLabel(QString::number(content->getYear()))),
    Subgenre(new QLabel(QString::fromStdString(content->getSubgenreString()))),
    Watched(new QLabel(content->getWatched() ? "Yes" : "No")),
    Starred(new QLabel(content->getStarred() ? "Yes" : "No")),
    Description(new QLabel(QString::fromStdString(content->getDescription()))),
    Type(new QLabel(QString::fromStdString(content->getType())))
{

    if(const Content* temp = library.searchId(content->getInspiration()); temp){
        Inspiration = new QLabel(QString::fromStdString(temp->getTitle()));
    }else{
        Inspiration = new QLabel("No inspiration");
    }

    format();
}

void AttributeDisplayWindow::format(){

    bigLayout = new QHBoxLayout(this); //Box orizzontale che contiene a sinistra l'immagine e destra gli dettagli del content

    auto *img = new QLabel();

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

    detailLayout->setAlignment(Qt::AlignTop);

    bigLayout->insertLayout(1, detailLayout);

    //Ogni campo ha un suo layout

    auto *titleLayout = new QFormLayout();
    Title->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    Year->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    titleLayout->addRow(Title);
    titleLayout->addRow(Year);
    detailLayout->addLayout(titleLayout);

    auto *descrLayout = new QFormLayout();
    descrLayout->setSpacing(5); //riduce lo spazio tra "Description :" e la descrizione
    descrLayout->addRow(new QLabel(QString("<h2>%1</h2>").arg("Description : ")));
    Description->setMaximumWidth(500);
    Description->setWordWrap(true);
    descrLayout->addRow(Description);
    detailLayout->addLayout(descrLayout);

    auto *typeLayout = new QFormLayout();
    typeLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Type : ")), Type);
    detailLayout->addLayout(typeLayout);

    QFormLayout *inspirationLayout = new QFormLayout();
    inspirationLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Inspired by: ")), Inspiration);
    detailLayout->addLayout(inspirationLayout);

    auto *subgenreLayout = new QFormLayout();
    subgenreLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Subgenre: ")), Subgenre);
    detailLayout->addLayout(subgenreLayout);
}

QVBoxLayout* AttributeDisplayWindow::getDetailLayout(){
    return detailLayout;
}

AttributeDisplayWindow::~AttributeDisplayWindow(){
}

