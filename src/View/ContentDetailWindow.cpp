#include "ContentDetailWindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

#include "DisplayWindows/AttributeDisplayWindow.h"
#include "../Model/lib/ScienceFictionLibrary.h"
#include "LibraryWindow.h"
#include "ContentEditWindow.h"

ContentDetailWindow::ContentDetailWindow(QWidget *parent)
    : QWidget(parent), m_content(nullptr), view(new Visitor())
{
    setupUI();
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ContentDetailWindow::setContent(Content* content) {
    m_content = content;
    updateContentDisplay();
}

void ContentDetailWindow::updateContentDisplay() {
    if (!m_content) return;

    delete(contentDetails);

    contentDetails = m_content->accept(view);
    m_mainLayout->insertWidget(1, contentDetails);
}

void ContentDetailWindow::setupUI() 
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    // Top bar with close button
    auto *topBarLayout = new QHBoxLayout();
    topBarLayout->addStretch();
    
    m_closeButton = new QPushButton("×");
    m_closeButton->setFixedSize(30, 30);
    m_closeButton->setStyleSheet("QPushButton { font-size: 18px; border: none; }");
    connect(m_closeButton, &QPushButton::clicked, this, &ContentDetailWindow::closeRequested);
    
    topBarLayout->addWidget(m_closeButton);
    m_mainLayout->addLayout(topBarLayout);

    // Content area
    contentDetails = new AttributeDisplayWindow();

    m_mainLayout->insertWidget(1, contentDetails);



    // Edit button at bottom
    auto *editButtonLayout = new QHBoxLayout();
    m_editButton = new QPushButton();
    m_editButton->setIcon(QIcon(":assets/icons/edit.png"));
    m_editButton->setToolTip("Edit current library content");
    m_editButton->setFixedSize(50, 50);
    connect(m_editButton, &QPushButton::clicked, this, &ContentDetailWindow::onEditClicked);
    
    editButtonLayout->addWidget(m_editButton);
    m_mainLayout->addLayout(editButtonLayout);

    auto *deleteButtonLayout = new QHBoxLayout();
    m_deleteButton = new QPushButton();
    m_deleteButton->setIcon(QIcon(":assets/icons/delete.png"));
    m_deleteButton->setToolTip("Delete current library content");
    m_deleteButton->setStyleSheet("QPushButton { color: red; }");
    m_deleteButton->setFixedSize(50, 50);
    connect(m_deleteButton, &QPushButton::clicked, this, &ContentDetailWindow::onDeleteClicked);
    
    deleteButtonLayout->addWidget(m_deleteButton);
    m_mainLayout->addLayout(deleteButtonLayout);

    // Style
    setStyleSheet(
        "ContentDetailWindow { background: rgba(255, 255, 255, 0.95); border-left: 1px solid #ddd; }"
        "QLabel { background: transparent; }"
    );
}

void ContentDetailWindow::onEditClicked() {
    if (m_content) {
        emit editRequested(m_content);
    }
}

void ContentDetailWindow::onDeleteClicked() {
    if (m_content) {
        ScienceFiction_Library::getInstance().removeContent(m_content);
        m_content = nullptr;
        emit contentDeleted();
        emit closeRequested();
    }
}

void ContentDetailWindow::refreshContent() {
    if (m_content) {
        updateContentDisplay();
    }
}
