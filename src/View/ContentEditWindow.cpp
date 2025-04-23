#include "ContentEditWindow.h"
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

ContentEditWindow::ContentEditWindow(Content* content, QWidget *parent): QDialog(parent), m_content(content) 
{
    if (!content) {
        qCritical() << "Null content passed to editor!";
        reject();
        return;
    }
    
    setWindowTitle("Edit Content - " + QString::fromStdString(content->getTitle()));
    setupUI();
    loadContentData();
}

void ContentEditWindow::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

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
    m_subgenreCombo = new QComboBox();
    m_subgenreCombo->addItems({
        "None", "Action", "Comedy", "Drama", "Horror", "Romance",
        "Thriller", "Mystery", "Adventure", "Western", "War",
        "Musical", "Family", "Sports", "Superhero"
    });
    formLayout->addRow("Subgenre:", m_subgenreCombo);

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
    
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(m_imagePathEdit);
    imageLayout->addWidget(m_browseButton);
    formLayout->addRow("Image Path:", imageLayout);

    mainLayout->addLayout(formLayout);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_saveButton = new QPushButton("Save Changes");
    connect(m_saveButton, &QPushButton::clicked, this, &ContentEditWindow::saveChanges);
    
    m_cancelButton = new QPushButton("Cancel");
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);
    mainLayout->addLayout(buttonLayout);
}

void ContentEditWindow::loadContentData() {
    m_titleEdit->setText(QString::fromStdString(m_content->getTitle()));
    m_yearSpin->setValue(m_content->getYear());
    m_subgenreCombo->setCurrentText(QString::fromStdString(m_content->getSubgenreString()));
    m_watchedCheck->setChecked(m_content->getWatched());
    m_starredCheck->setChecked(m_content->getStarred());
    m_descEdit->setPlainText(QString::fromStdString(m_content->getDescription()));
    m_imagePathEdit->setText(QString::fromStdString(m_content->getImage()));
}

void ContentEditWindow::saveChanges() {
    m_content->setTitle(m_titleEdit->text().toStdString());
    m_content->setYear(m_yearSpin->value());
    //m_content->setSubgenreFromString(m_subgenreCombo->currentText().toStdString());
    m_content->setWatched(m_watchedCheck->isChecked());
    m_content->setStarred(m_starredCheck->isChecked());
    m_content->setDescription(m_descEdit->toPlainText().toStdString());
    m_content->setImage(m_imagePathEdit->text().toStdString());

    emit contentUpdated();
    accept();
}

void ContentEditWindow::browseImage() {
    QString file = QFileDialog::getOpenFileName(
        this,
        "Select Image",
        QDir::homePath(),
        "Image Files (*.png *.jpg *.jpeg)"
    );
    
    if(!file.isEmpty()) {
        m_imagePathEdit->setText(file);
    }
}