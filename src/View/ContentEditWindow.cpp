#include "ContentEditWindow.h"
#include "LibraryWindow.h"
#include "../Model/lib/Content.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QPushButton>

#include "EditWindows/CommonEditWindow.h"
#include "EditWindows/EditVisitor.h"

ContentEditWindow::ContentEditWindow(Content* content, QWidget *parent): QDialog(parent), m_content(content), editVis()
{
    if (!content) {
        qCritical() << "Null content passed to editor!";
        reject();
        return;
    }
    
    setWindowTitle("Edit Content - " + QString::fromStdString(content->getTitle()));
    setupUI();
}

void ContentEditWindow::setupUI() {


    mainLayout = new QVBoxLayout(this);
    /*{
    auto *formLayout = new QFormLayout();

    // Type (read-only)
    m_typeLabel = new QLabel(QString::fromStdString(m_content->getType())); // Initialize the label
    formLayout->addRow("Type:", m_typeLabel);

    // Title
    m_titleEdit = new QLineEdit();
    formLayout->addRow("Title:", m_titleEdit);

    // Year
    m_yearSpin = new QSpinBox();
    m_yearSpin->setRange(1900, QDate::currentDate().year());
    formLayout->addRow("Year:", m_yearSpin);

    // Subgenre
    m_subgenreContainer = new QWidget();
    auto *subgenreLayout = new QVBoxLayout(m_subgenreContainer);
    
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
        m_subgenreCheckboxes.append(checkbox);
        subgenreLayout->addWidget(checkbox);
    }
    
    formLayout->addRow("Subgenres:", m_subgenreContainer);

    // Watched/Starred
    m_watchedCheck = new QCheckBox();
    formLayout->addRow("Watched:", m_watchedCheck);
    
    m_starredCheck = new QCheckBox();
    formLayout->addRow("Starred:", m_starredCheck);

    // Description
    m_descEdit = new QTextEdit();
    formLayout->addRow("Description:", m_descEdit);

    // Image path
    m_imagePathEdit = new QLineEdit();
    m_browseButton = new QPushButton("Browse...");
    connect(m_browseButton, &QPushButton::clicked, this, &ContentEditWindow::browseImage);
    
    auto *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(m_imagePathEdit);
    imageLayout->addWidget(m_browseButton);
    formLayout->addRow("Image Path:", imageLayout);

    mainLayout->addLayout(formLayout);
    }
    */

    contentEditWindow = new CommonEditWindow;
    mainLayout->insertWidget(0, contentEditWindow);
    // Buttons
    auto *buttonLayout = new QHBoxLayout();
    m_saveButton = new QPushButton("Save Changes");
    connect(m_saveButton, &QPushButton::clicked, this, &ContentEditWindow::saveChanges);
    
    m_cancelButton = new QPushButton("Cancel");
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);
    mainLayout->insertLayout(-1, buttonLayout);
}
/*
void ContentEditWindow::loadContentData() {
    m_titleEdit->setText(QString::fromStdString(m_content->getTitle()));
    m_yearSpin->setValue(m_content->getYear());
    //m_subgenreCombo->setCurrentText(QString::fromStdString(m_content->getSubgenreString()));
    m_watchedCheck->setChecked(m_content->getWatched());
    m_starredCheck->setChecked(m_content->getStarred());
    m_descEdit->setPlainText(QString::fromStdString(m_content->getDescription()));
    m_imagePathEdit->setText(QString::fromStdString(m_content->getImage()));

    int currentSubgenres = m_content->getSubgenre();
    for (int i = 0; i < m_subgenreCheckboxes.size(); i++) {
        // Verifica se il bit corrispondente è attivo
        unsigned int bitValue = 1 << i;
        m_subgenreCheckboxes[i]->setChecked((currentSubgenres & bitValue) != 0);
    }
}*/

void ContentEditWindow::updateEditWindow(){
    if (!m_content) return;

    delete(m_content);

    contentEditWindow = m_content->acceptEdit(editVis);
    mainLayout->insertWidget(0, contentEditWindow);
}

void ContentEditWindow::saveChanges() {
    contentEditWindow->saveEdit();
    emit contentUpdated();
    accept();
}
