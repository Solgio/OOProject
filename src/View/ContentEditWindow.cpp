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
    auto *buttonContainer = new QWidget();
    buttonContainer->setFixedHeight(60); // Fixed height to prevent cutting
    auto *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(0, 10, 0, 10); // Top and bottom margins
    buttonLayout->setSpacing(10); 

    m_restoreButton = new QPushButton();
    m_restoreButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_restoreButton->setFixedSize(40,40);
    m_restoreButton->setToolTip("Restore original content");
    m_restoreButton->setIcon(QIcon(":assets/icons/reverse.png"));
    m_restoreButton->setIconSize(QSize(30, 30));
    connect(m_restoreButton, &QPushButton::clicked, this, &ContentEditWindow::restoreChanges);

    m_saveButton = new QPushButton();
    m_saveButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_saveButton->setFixedSize(40,40);
    m_saveButton->setToolTip("Save changes to the content");
    m_saveButton->setIcon(QIcon(":assets/icons/save_edit.png"));
    m_saveButton->setIconSize(QSize(35, 35));
    connect(m_saveButton, &QPushButton::clicked, this, &ContentEditWindow::saveChanges);
    
    m_cancelButton = new QPushButton("X");
    m_cancelButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_cancelButton->setFixedSize(40,40);
    m_cancelButton->setStyleSheet("QPushButton { color: red; font-size: 35px }");
    m_cancelButton->setToolTip("Cancel changes and close editor");

    connect(m_cancelButton, &QPushButton::clicked, this, &ContentEditWindow::cancelChanges);
    
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_restoreButton);
    buttonLayout->addWidget(m_cancelButton);
    mainLayout->addWidget(buttonContainer);
}

void ContentEditWindow::setContent(Content *content){
    m_content = content;
    updateEditWindow();
}

void ContentEditWindow::updateEditWindow(){
    if(contentEditWindow){
        contentEditLayout->removeWidget(contentEditWindow); //rimuove dal Layout ma non lo elimina nè nasconde
        contentEditLayout->setParent(nullptr);
        contentEditWindow->deleteLater();
        contentEditWindow = nullptr; //resetto il puntatore
    }

    contentEditWindow = m_content->acceptEdit(editVis);
    if (contentEditWindow) {
        contentEditLayout->addWidget(contentEditWindow);
    }
}

void ContentEditWindow::restoreChanges() {

    QCoreApplication::processEvents();

    updateEditWindow();
}

void ContentEditWindow::saveChanges() {
    contentEditWindow->saveEdit();
    emit contentUpdated();
}

void ContentEditWindow::cancelChanges() {
    emit closeRequested();
}
