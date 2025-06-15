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

#include "Visitor.h"
#include "EditWindows/CommonEditWindow.h"
#include "EditWindows/BookEditWindow.h"
#include "EditWindows/ComicEditWindow.h"
#include "EditWindows/FilmEditWindow.h"
#include "EditWindows/SerieEditWindow.h"
#include "EditWindows/VideoGameEditWindow.h"

ContentEditWindow::ContentEditWindow(Content* content, QWidget *parent): QWidget(parent), m_content(content)
{
    if (!content) {
        qCritical() << "Null content passed to editor!";
        cancelChanges();
        return;
    }
    
    setWindowTitle("Edit Content - " + QString::fromStdString(content->getTitle()));
    editVis = new Visitor();
    setupUI();
}

void ContentEditWindow::setupUI() {


    mainLayout = new QVBoxLayout(this);

    //Creazione del Scroll area per Il content
    scrollAreaForEditWindow = new QScrollArea();
    scrollAreaForEditWindow->setWidgetResizable(true);
    scrollAreaForEditWindow->setFrameShape(QFrame::NoFrame);
    scrollAreaForEditWindow->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);


    //creazione il layout per contentEditWindow
    contentEditLayout = new QVBoxLayout();
    contentEditLayout->setSizeConstraint(QLayout::SetNoConstraint);
    //creazione del widget per contenere contentEditLayout
    scrollWidget = new QWidget;
    scrollWidget->setLayout(contentEditLayout);
    //Inserisco il layout nella scrollArea
    scrollAreaForEditWindow->setWidget(scrollWidget);
    //Metto lo Scroll Area nel mainLayout nella prima posizione
    mainLayout->insertWidget(0, scrollAreaForEditWindow);

    // Buttons
    auto *buttonLayout = new QGridLayout();

    m_restoreButton = new QPushButton("Restore");
    connect(m_restoreButton, &QPushButton::clicked, this, &ContentEditWindow::restoreChanges);

    m_saveButton = new QPushButton("Save Changes");
    connect(m_saveButton, &QPushButton::clicked, this, &ContentEditWindow::saveChanges);
    
    m_cancelButton = new QPushButton("Cancel");
    connect(m_cancelButton, &QPushButton::clicked, this, &ContentEditWindow::cancelChanges);
    
    buttonLayout->addWidget(m_saveButton, 0 , 0, Qt::AlignRight);
    buttonLayout->addWidget(m_restoreButton, 0, 1, Qt::AlignHCenter);
    buttonLayout->addWidget(m_cancelButton, 0 , 2, Qt::AlignLeft);
    mainLayout->insertLayout(-1, buttonLayout);
}

void ContentEditWindow::setContent(Content *content){
    m_content = content;
    updateEditWindow();
}

void ContentEditWindow::updateEditWindow(){
    //se è la prima volta che viene creata allora lo aggiungo al layout
    if(contentEditWindow){
        contentEditWindow->deleteLater();
    }

    contentEditWindow = m_content->acceptEdit(editVis);
    contentEditLayout->addWidget(contentEditWindow);

    if(contentEditWindow->isHidden()){
        contentEditWindow->show();
    }
    connect(contentEditWindow, &CommonEditWindow::typeUpdated, this, &ContentEditWindow::changeType);
}

void ContentEditWindow::changeType(int index) { //TODO da modificare

    if(contentTypeEditWindow){
        contentTypeEditWindow->deleteLater();
    }

    switch (index) {
    case 0:
        contentTypeEditWindow = new BookEditWindow(m_content);
        break;
    case 1:
        contentTypeEditWindow = new ComicEditWindow(m_content);
        break;
    case 2:
        contentTypeEditWindow = new FilmEditWindow(m_content);
        break;
    case 3:
        contentTypeEditWindow = new SerieEditWindow(m_content);
        break;
    case 4:
        contentTypeEditWindow = new VideoGameEditWindow(m_content);
        break;
    default:
        break;
    }
    //contentEditLayout->removeWidget(contentEditWindow); //rimuove dal Layout ma non lo elimina nè nasconde //! NON SERVE RIMUOVERLO DAL LAYOUT
    contentEditWindow->hide(); //nascondo il contentEditWindow
    contentEditLayout->addWidget(contentTypeEditWindow);
    connect(contentTypeEditWindow, &CommonEditWindow::typeUpdated, this, &ContentEditWindow::changeType);
}

void ContentEditWindow::restoreChanges() {
    //se eseite il contentTypeEditWindow lo elimino e lo rimuovo dal contentEditLayout
    if(contentTypeEditWindow){
        delete(contentTypeEditWindow);
        contentTypeEditWindow = nullptr;
    }
    //uso la funzione già esistente per visualizzare il content originale
    updateEditWindow();
}

void ContentEditWindow::saveChanges() {
    contentEditWindow->saveEdit();
    emit contentUpdated();
}

void ContentEditWindow::cancelChanges() {
    emit closeRequested();
}
