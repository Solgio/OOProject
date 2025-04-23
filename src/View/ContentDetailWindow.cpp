#include "ContentDetailWindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

ContentDetailWindow::ContentDetailWindow(QWidget *parent)
    : QWidget(parent), m_content(nullptr) 
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

    QString html = QString(
        "<div style='margin:10px;'>"
        "<h2>%1</h2>"
        "<div style='float:right; margin-left:20px;'>"
        "<img src='%2' width='200' onerror=\"this.src=':assets/icons/default.png'\">"
        "</div>"
        "<p><b>Type:</b> %8</p>"
        "<p><b>Year:</b> %3</p>"
        "<p><b>Genre:</b> %4</p>"
        "<p><b>Watched:</b> %5</p>"
        "<p><b>Starred:</b> %6</p>"
        "<p><b>Description:</b><br>%7</p>"
        "</div>"
    ).arg(
        QString::fromStdString(m_content->getTitle()),
        QString::fromStdString(m_content->getImage()),
        QString::number(m_content->getYear()),
        QString::fromStdString(m_content->getSubgenreString()),
        m_content->getWatched() ? "Yes" : "No",
        m_content->getStarred() ? "Yes" : "No",
        QString::fromStdString(m_content->getDescription()),
        QString::fromStdString(m_content->getType())
    );
    m_contentDetails->setText(html);
}

void ContentDetailWindow::setupUI() 
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    // Top bar with close button
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    topBarLayout->addStretch();
    
    m_closeButton = new QPushButton("×");
    m_closeButton->setFixedSize(30, 30);
    m_closeButton->setStyleSheet("QPushButton { font-size: 18px; border: none; }");
    connect(m_closeButton, &QPushButton::clicked, this, &ContentDetailWindow::closeRequested);
    
    topBarLayout->addWidget(m_closeButton);
    m_mainLayout->addLayout(topBarLayout);

    // Content area
    m_contentDetails = new QLabel();
    m_contentDetails->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_contentDetails->setWordWrap(true);
    m_contentDetails->setTextFormat(Qt::RichText);
    m_mainLayout->addWidget(m_contentDetails);

    // Edit button at bottom
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_editButton = new QPushButton();
    m_editButton->setIcon(QIcon(":assets/icons/edit.png"));
    m_editButton->setToolTip("Edit current library content");
    connect(m_editButton, &QPushButton::clicked, this, &ContentDetailWindow::onEditClicked);
    
    buttonLayout->addWidget(m_editButton);
    m_mainLayout->addLayout(buttonLayout);

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