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
#include "Visitor.h"
#include "EditWindows/SerieEditWindow.h"

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
    auto *buttonLayout = new QHBoxLayout();
    m_saveButton = new QPushButton("Save Changes");
    connect(m_saveButton, &QPushButton::clicked, this, &ContentEditWindow::saveChanges);
    
    m_cancelButton = new QPushButton("Cancel");
    connect(m_cancelButton, &QPushButton::clicked, this, &ContentEditWindow::cancelChanges);
    
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);
    mainLayout->insertLayout(-1, buttonLayout);
}

void ContentEditWindow::setContent(Content *content){
    m_content = content;
    updateEditWindow();
}

void ContentEditWindow::updateEditWindow(){
    /*if(contentEditWindow){
        delete(contentEditWindow);
    }*/
    //Da segmentation fault
    //Non so perchè e non so neanchè se verrà pulito con la creazione del nuovo

    contentEditWindow = m_content->acceptEdit(editVis);
    contentEditLayout->addWidget(contentEditWindow);
    connect(contentEditWindow, &CommonEditWindow::typeUpdated, this, &ContentEditWindow::changeType);
}

void ContentEditWindow::changeType() { //TODO da modificare

    if(contentTypeEditWindow == nullptr){
        contentTypeEditWindow = new SerieEditWindow();
        contentEditLayout->removeWidget(contentEditWindow); //rimuove dal Layout ma non lo elimina nè nasconde
        contentEditWindow->hide(); //nascondo il widget rimosso se no fa overlap
        contentEditLayout->addWidget(contentTypeEditWindow);
        contentEditLayout->update();
    }else{
        delete(contentTypeEditWindow);
        contentTypeEditWindow = new SerieEditWindow();
        contentEditLayout->addWidget(contentTypeEditWindow);
    }
    //stessa cosa del updateEditWindow()
}

void ContentEditWindow::saveChanges() {
    contentEditWindow->saveEdit();
    emit contentUpdated();
}

void ContentEditWindow::cancelChanges() {
    emit closeRequested();
}
