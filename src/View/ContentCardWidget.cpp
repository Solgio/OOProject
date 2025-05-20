#include "ContentCardWidget.h"
#include <QFile>
#include <QEvent>
#include <QVariant>

ContentCardWidget::ContentCardWidget(Content *content, QWidget *parent)
    : QWidget(parent), m_content(content) {
    setObjectName("ContentCard");
    setFixedSize(180, 400); // Fixed size for consistency
    setCursor(Qt::PointingHandCursor);
    installEventFilter(this); // Filter events on itself
    setProperty("content_ptr", QVariant::fromValue(m_content)); // Store content pointer
    setupUI();
    updateCardStyle(); // Set initial style
}

void ContentCardWidget::setupUI() {
    auto *cardLayout = new QVBoxLayout(this);
    cardLayout->setContentsMargins(8, 8, 8, 8);
    cardLayout->setSpacing(5);
    cardLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    m_coverLabel = new QLabel();
    m_coverLabel->setFixedSize(164, 240);
    m_coverLabel->setAlignment(Qt::AlignCenter);
    m_coverLabel->setStyleSheet("background-color: transparent;");

    m_titleLabel = new QLabel(QString::fromStdString(m_content->getTitle()));
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

    m_typeLabel = new QLabel(QString::fromStdString(m_content->getType()));
    m_typeLabel->setAlignment(Qt::AlignCenter);
    m_typeLabel->setStyleSheet("background-color: transparent");

    m_genreLabel = new QLabel(QString::fromStdString(m_content->getSubgenreString()));
    m_genreLabel->setAlignment(Qt::AlignCenter);
    m_genreLabel->setStyleSheet("background-color: transparent");

    m_yearLabel = new QLabel(QString::number(m_content->getYear()));
    m_yearLabel->setAlignment(Qt::AlignCenter);

    m_statusLayout = new QHBoxLayout();
    m_statusLayout->setAlignment(Qt::AlignCenter);
    m_statusLayout->setSpacing(10); // Spacing between status labels

    // Add elements to card
    cardLayout->addWidget(m_coverLabel);
    cardLayout->addWidget(m_titleLabel);
    cardLayout->addWidget(m_typeLabel);
    cardLayout->addWidget(m_genreLabel);
    cardLayout->addWidget(m_yearLabel);
    cardLayout->addLayout(m_statusLayout);
    cardLayout->addStretch(); // Push content to top

    // Set cover image
    auto coverPath = QString::fromStdString(m_content->getImage());
    if (!coverPath.isEmpty() && QFile::exists(coverPath)) {
        m_coverLabel->setPixmap(QPixmap(coverPath).scaled(m_coverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        m_coverLabel->setPixmap(QPixmap(":assets/icons/no-image.png").scaled(m_coverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // Update status labels
    if (m_content->getWatched()) {
        auto *watchedLabel = new QLabel("✓ Watched");
        watchedLabel->setStyleSheet("color: green;");
        m_statusLayout->addWidget(watchedLabel);
    }
    if (m_content->getStarred()) {
        auto *starredLabel = new QLabel("★ Starred");
        starredLabel->setStyleSheet("color: orange;");
        m_statusLayout->addWidget(starredLabel);
    }
}

void ContentCardWidget::setSelected(bool selected) {
    if (m_isSelected != selected) {
        m_isSelected = selected;
        updateCardStyle();
    }
}

void ContentCardWidget::updateCardStyle() {
    if (m_isSelected) {
        setStyleSheet("QWidget#ContentCard { border: 2px solid #00FF00; border-radius: 5px; background-color: transparent; }");
    } else if (m_content->getStarred()) {
        setStyleSheet("QWidget#ContentCard { border: 2px solid #FFD700; border-radius: 5px; background-color: transparent; }");
    } else {
        setStyleSheet("QWidget#ContentCard { border: 1px solid #ccc; border-radius: 5px; background-color: transparent; }");
    }
}

bool ContentCardWidget::eventFilter(QObject* obj, QEvent* event) {
    if (obj == this) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            emit doubleClicked(m_content);
            return true;
        } else if (event->type() == QEvent::MouseButtonPress) {
            emit singleClicked(m_content);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}