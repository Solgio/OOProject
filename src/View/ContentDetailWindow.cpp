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
    : QWidget(parent)
{
    setupUI();
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

ContentDetailWindow::~ContentDetailWindow() {
    // Remove contentDetails from layout first before deleting
    if (contentDetails && m_mainLayout) {
        m_mainLayout->removeWidget(contentDetails);
        contentDetails->setParent(nullptr); // Unparent before deletion
        contentDetails->deleteLater();
        contentDetails = nullptr;
    }
}
void ContentDetailWindow::setContent(Content* content) {
    m_content = content;
    updateContentDisplay();
}

void ContentDetailWindow::updateContentDisplay() {
    if (!m_content) return;

    if (contentDetails) {
        m_mainLayout->removeWidget(contentDetails);
        contentDetails->setParent(nullptr); // Unparent before deletion
        contentDetails->deleteLater();
        contentDetails = nullptr;
    }

    // Crea il nuovo widget
    contentDetails = m_content->accept(view);
    if (contentDetails) {
        m_mainLayout->insertWidget(1, contentDetails);
    }
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
    auto *editDeleteButtonLayout = new QHBoxLayout();
    editDeleteButtonLayout->addStretch(1); 
    editDeleteButtonLayout->setContentsMargins(0, 0, 0, 40);

    m_editButton = new QPushButton();
    m_editButton->setIcon(QIcon(":assets/icons/edit.png"));
    m_editButton->setToolTip("Edit current library content");
    m_editButton->setFixedSize(40, 40);
    m_editButton->setIconSize(QSize(35, 35));
    connect(m_editButton, &QPushButton::clicked, this, &ContentDetailWindow::onEditClicked);
    editDeleteButtonLayout->addWidget(m_editButton);

    m_deleteButton = new QPushButton();
    m_deleteButton->setIcon(QIcon(":assets/icons/delete.png"));
    m_deleteButton->setToolTip("Delete current library content");
    m_deleteButton->setStyleSheet("QPushButton { color: red; }");
    m_deleteButton->setFixedSize(40, 40);
    m_deleteButton->setIconSize(QSize(35, 35));
    connect(m_deleteButton, &QPushButton::clicked, this, &ContentDetailWindow::onDeleteClicked);
    editDeleteButtonLayout->addWidget(m_deleteButton);
    editDeleteButtonLayout->addStretch(1);

    m_mainLayout->addLayout(editDeleteButtonLayout);

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
