#include <QStandardItemModel>
#include "CommonEditWindow.h"
#include "../../Model/lib/Content.h"
#include "../../Model/lib/ScienceFictionLibrary.h"

CommonEditWindow::CommonEditWindow(QWidget *parent):
    QWidget(parent),
    library(ScienceFiction_Library::getInstance()),
    titleEdit(new QTextEdit()), // ?? da testare
    imgEdit(new QTextEdit()),
    yearEdit(new MySpinBox()),
    inspEdit(new MyComboBox()),
    watchedEdit(new QCheckBox("Watched")),
    starredEdit(new QCheckBox("Starred")),
    descEdit(new QTextEdit()),
    typeEdit(new MyComboBox())
{
    format();
}

CommonEditWindow::CommonEditWindow(Content *content, QWidget *parent):
    QWidget(parent),
    library(ScienceFiction_Library::getInstance()),
    titleEdit(new QTextEdit("<h1>" + QString::fromStdString(content->getTitle()) + "</h1>")), // ?? da testare
    imgEdit(new QTextEdit(QString::fromStdString(content->getImage()))),
    yearEdit(new MySpinBox()),
    inspEdit(new MyComboBox()),
    watchedEdit(new QCheckBox("Watched")),
    starredEdit(new QCheckBox("Starred")),
    descEdit(new QTextEdit(QString::fromStdString(content->getDescription()))),
    typeEdit(new MyComboBox()),
    contentPtr(content)
{
    yearEdit->setMaximum(9999);
    yearEdit->setValue(content->getYear());
    watchedEdit->setChecked(content->getWatched());
    starredEdit->setChecked(content->getStarred());

    //Creo una "tabella" di n righe e 2 colonne
    QStandardItemModel *model = new QStandardItemModel();

    QList<QStandardItem*> listaNomi;
    QList<QStandardItem*> listaId;

    //Creazione del QList<QStandardItem*> per Tutti i nomi e ID dei content della Libreria
    listaNomi.append(new QStandardItem("No Inspiration"));
    listaId.append(new QStandardItem()); //"No Inspiration" non ha ID
    for(const auto &v_content : library.getContentList()){
        listaNomi.append(new QStandardItem(QString::fromStdString(v_content->getTitle())));
        listaId.append(new QStandardItem(QString::number(v_content->getId())));
    }
    model->appendColumn(listaNomi);
    model->appendColumn(listaId);
    //inserisco nel comboBox la "tabella"
    inspEdit->setModel(model); //di default viene mostrato la prima colonna

    inspEdit->setEditable(false); //se non è editabile cambia l'indice in corrispondenza del testo

    //cerca nella libreria il titolo del corrispondente all'ID dell'Inspiration
    if(const Content* temp = library.searchId(content->getInspiration()); temp){
        inspEdit->setCurrentText(QString::fromStdString(temp->getTitle()));
    }else{
        inspEdit->setCurrentIndex(0); // Se non trova la inspiration del content mostra "No Inspiration"
    }

    format();
}

void CommonEditWindow::format(){

    bigLayout = new QHBoxLayout(this);
    bigLayout->setAlignment(Qt::AlignVCenter);

    imgLayout = new QFormLayout();{

        auto *img = new QLabel();
        if (!imgEdit->toPlainText().isEmpty() && QFile::exists(imgEdit->toPlainText())) {
            img->setPixmap(QPixmap(imgEdit->toPlainText()).scaled(500,500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            img->setAlignment(Qt::AlignCenter);
        } else {
            img->setPixmap(QPixmap(":assets/icons/no-image.png").scaled(500,500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }

        img->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        imgLayout->addRow(img);

        auto *imagePath = new QLabel("Image Path:");
        imagePath->setBuddy(imgEdit);

        searchBotton = new QPushButton("Browse...");
        connect(searchBotton, &QPushButton::clicked, this, &CommonEditWindow::browseImage);

        imgLayout->addRow(imagePath, searchBotton);
    }

    bigLayout->addLayout(imgLayout);

    detailEditLayout = new QVBoxLayout(); //Box verticale per gli dettagli del content
    detailEditLayout->setSpacing(15);
    detailEditLayout->setAlignment(Qt::AlignTop);

    bigLayout->insertLayout(1, detailEditLayout);

    //Creazione della finestra dei sottoGeneri
    subgenreWindow = new QWidget();
    QVBoxLayout *subgenreBox = new QVBoxLayout();
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
    subgenreWindow->setLayout(subgenreBox);

    //Caricare i subgenre
    int currentSubgenres = contentPtr->getSubgenre();
    for (int i = 0; i < subEdit.size(); i++) {
        // Verifica se il bit corrispondente è attivo
        unsigned int bitValue = 1 << i;
        subEdit[i]->setChecked((currentSubgenres & bitValue) != 0);
    }

    //Creazione del comboBox typeEdit
    const QStringList types = {
        "Book", //0
        "Comic", //1
        "Film", //2
        "Serie", //3
        "VideoGame" //4
    };
    typeEdit->addItems(types);
    typeEdit->setEditable(false);
    typeEdit->setInsertPolicy(QComboBox::NoInsert);
    connect(typeEdit, &MyComboBox::currentIndexChanged, this, &CommonEditWindow::changeType);


    //Ogni campo ha un suo layout

    //Titolo e Year
    auto *titleLayout = new QFormLayout();
    titleLayout->setAlignment(Qt::AlignHCenter);
    titleLayout->addRow(new QLabel(QString("<h1>%1</h1>").arg("Title")), titleEdit);
    titleLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Year")), yearEdit);
    detailEditLayout->addLayout(titleLayout);

    //Descrizione
    auto *descrLayout = new QFormLayout();
    descrLayout->setSpacing(5);
    descrLayout->addRow(new QLabel(QString("<h2>%1</h2>").arg("Descrizione : ")));
    descrLayout->addRow(descEdit);
    detailEditLayout->addLayout(descrLayout);

    //Inspiration name
    auto *inspirationLayout = new QFormLayout();
    QLabel *inspLabel = new QLabel(QString("<h3>%1</h3>").arg("Inspired by: "));
    inspLabel->setBuddy(inspEdit);
    inspEdit->setMaximumHeight(30);
    inspEdit->setMaximumWidth(300);
    inspirationLayout->addRow(inspLabel, inspEdit);
    detailEditLayout->addLayout(inspirationLayout);

    //Checkboxes per Starred e Watched
    auto *starredWatchedLayout = new QFormLayout();
    starredWatchedLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Status : ")));
    starredWatchedLayout->addRow(starredEdit, watchedEdit);
    detailEditLayout->addLayout(starredWatchedLayout);

    //Lista di subgenre
    auto *subgenreLayout = new QFormLayout();
    subgenreLayout->setSpacing(5);
    subgenreLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Subgenre : ")));
    subgenreLayout->addRow(subgenreWindow);
    detailEditLayout->addLayout(subgenreLayout);

    //Selezione del type
    auto *typeLayout = new QFormLayout();
    typeLayout->setAlignment(Qt::AlignHCenter);
    typeLayout->addRow(new QLabel(QString("<h3>%1</h3>").arg("Type : ")), typeEdit);
    detailEditLayout->addLayout(typeLayout);

}

void CommonEditWindow::browseImage() {
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

void CommonEditWindow::changeType(int i) {
    emit typeUpdated(i);
}

void CommonEditWindow::saveEdit(){
    if(contentPtr){
        contentPtr->setTitle(titleEdit->toPlainText().QString::toStdString());
        contentPtr->setImage(imgEdit->toPlainText().QString::toStdString());
        contentPtr->setYear(yearEdit->value());
        contentPtr->setInspiration(inspEdit->model()->itemData(inspEdit->model()->index(inspEdit->currentIndex(), 1)).value(0).toInt());
        contentPtr->setStarred(starredEdit->isChecked());
        contentPtr->setWatched(watchedEdit->isChecked());
        contentPtr->setDescription(descEdit->toPlainText().QString::toStdString());

        unsigned int newSubgenres = 0;
        for (int i = 0; i < subEdit.size(); i++) {
            if (subEdit[i]->isChecked()) {
                unsigned int bitValue = 1 << i;
                newSubgenres |= bitValue;
            }
        }

        contentPtr->setSubgenre(newSubgenres);

        emit contentUpdated();
    }
}

QVBoxLayout* CommonEditWindow::getLayout() const{
    return detailEditLayout;
}

MyComboBox* CommonEditWindow::getTypeEditBox() const{
    return typeEdit;
}

Content* CommonEditWindow::getContent() const{
    return contentPtr;
}
