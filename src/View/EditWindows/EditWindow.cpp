#include "EditWindow.h"
#include "../../Model/lib/Content.h"

//include di tutti i concreti EditWindows
#include "BookEditWindow.h"
#include "ComicEditWindow.h"
#include "FilmEditWindow.h"
#include "SerieEditWindow.h"
#include "VideogameEditWindow.h"


EditWindow::EditWindow(Content *content, QWidget *parent): QWidget(parent),
    titleEdit(new QTextEdit("<h1>" + QString::fromStdString(content->getTitle()) + "</h1>")), // ?? da testare
    imgEdit(new QTextEdit(QString::fromStdString(content->getImage()))),
    yearEdit(new QSpinBox()),
    watchedEdit(new QCheckBox("Watched")),
    starredEdit(new QCheckBox("Starred")),
    descEdit(new QTextEdit(QString::fromStdString(content->getDescription()))),
    typeEdit(new QComboBox())
{
    yearEdit->setValue(content->getYear());
    watchedEdit->setTristate(content->getWatched());
    starredEdit->setTristate(content->getStarred());

    //Creazione della finestra dei sottoGeneri
    subgenreWindow = new QWidget();
    QVBoxLayout *subgenreBox = new QVBoxLayout(subgenreWindow);
    // Crea un checkbox per ogni subgenre
    const QStringList subgenres = {
        "Action",
        "Comedy",
        "Drama",
        "Horror",
        "Romance",
        "Thriller",
        "Mystery",
        "Adventure",
        "Western",
        "War",
        "Musical",
        "Family",
        "Sports",
        "Superhero"
    };
    for (const QString &subgenre : subgenres) {
        auto *checkbox = new QCheckBox(subgenre);
        subEdit.append(checkbox);
        subgenreBox->addWidget(checkbox);
    }

    //Creazione del comboBox typeEdit
    const QStringList types = {
        "Content", //index 0
        "Book", //1
        "Comic", //2
        "Film", //3
        "Serie", //4
        "VideoGame" //5
    };
    typeEdit->addItems(types);
    typeEdit->setEditable(false);
    typeEdit->setInsertPolicy(QComboBox::NoInsert);
    if(dynamic_cast<Book*>(content)){typeEdit->setCurrentText("Book");}
    else if(dynamic_cast<Comic*>(content)){typeEdit->setCurrentText("Comic");}
    else if(dynamic_cast<Film*>(content)){typeEdit->setCurrentText("Film");}
    else if(dynamic_cast<Serie*>(content)){typeEdit->setCurrentText("Serie");}
    else if(dynamic_cast<VideoGame*>(content)){typeEdit->setCurrentText("VideoGame");}
    else {typeEdit->setCurrentText("Content");} //Se fallisce, non ha nessun tipo concreto
    format();
}

void EditWindow::format(){

    bigLayout = new QHBoxLayout(this);

    imgLayout = new QFormLayout();{

    QLabel *img = new QLabel();
    img->setPixmap(QPixmap(imgEdit->toPlainText()));

    img->setMaximumSize(500, 500);
    img->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    imgLayout->addRow(img);

    QLabel *imagePath = new QLabel("Image Path:");
    imagePath->setBuddy(imgEdit);

    searchBotton = new QPushButton("Browse...");
    connect(searchBotton, &QPushButton::clicked, this, &EditWindow::browseImage);

    imgLayout->addRow(imagePath, searchBotton);
    }

    bigLayout->addLayout(imgLayout);

    detailEditLayout = new QVBoxLayout(); //Box verticale per gli dettagli del content
    detailEditLayout->setSpacing(15);
    detailEditLayout->setAlignment(Qt::AlignTop);

    bigLayout->insertLayout(1, detailEditLayout);

    //Ogni campo ha un suo layout

    //Titolo
    QFormLayout *titleLayout = new QFormLayout();
    titleLayout->setAlignment(Qt::AlignHCenter);
    titleLayout->addRow(new QLabel(QString("<h1>%1</h1>").arg("Title")), titleEdit);
    titleLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Year")), yearEdit);
    detailEditLayout->addLayout(titleLayout);

    //Descrizione
    QFormLayout *descrLayout = new QFormLayout();
    descrLayout->setSpacing(5);
    descrLayout->addRow(new QLabel(QString("<h2>%1</h2>").arg("Descrizione : ")));
    descrLayout->addRow(descEdit);
    detailEditLayout->addLayout(descrLayout);

    //Checkboxes per Starred e Watched
    QFormLayout *starredWatchedLayout = new QFormLayout();
    starredWatchedLayout->addRow(starredEdit, watchedEdit);

    //Lista di subgenre
    QFormLayout *subgenreLayout = new QFormLayout();
    subgenreLayout->setSpacing(5);
    subgenreLayout->addRow(new QLabel(QString("<h2>%1</h2>").arg("Subgenre : ")));
    subgenreLayout->addRow(subgenreWindow);
    detailEditLayout->addLayout(subgenreLayout);

    //Selezione del type
    QFormLayout *typeLayout = new QFormLayout();
    typeLayout->setAlignment(Qt::AlignHCenter);
    typeLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Type : ")), typeEdit);
    detailEditLayout->addLayout(typeLayout);
}


void EditWindow::browseImage() {
    QString file = QFileDialog::getOpenFileName(
        this,
        "Select Image",
        QDir::homePath(),
        "Image Files (*.png *.jpg *.jpeg)"
        );

    if(!file.isEmpty()) {
        imgEdit->setText(file);
    }
}
