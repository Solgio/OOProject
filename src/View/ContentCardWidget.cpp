#include "ContentCardWidget.h"
#include <QFile>
#include <QEvent>
#include <QVariant>

ContentCardWidget::ContentCardWidget(Content *content, QWidget *parent)
    : QWidget(parent), m_content(content) {
    setObjectName("ContentCard");
    setFixedSize(200, 400); // Fixed size for consistency
    setCursor(Qt::PointingHandCursor);
    installEventFilter(this); // Filter events on itself
    setProperty("content_ptr", QVariant::fromValue(m_content)); // Store content pointer
    setupUI();
    updateCardStyle(); // Set initial style
}

void ContentCardWidget::setupUI() {
    auto *cardLayout = new QVBoxLayout(this);
    cardLayout->setAlignment(Qt::AlignTop );

    m_cardFrame = new QFrame();
    m_cardFrame->setObjectName("ContentCardFrame"); 
    m_cardFrame->setFrameShape(QFrame::StyledPanel); 
    m_cardFrame->setFrameShadow(QFrame::Plain);      
    m_cardFrame->setLineWidth(0);                  
    m_cardFrame->setMidLineWidth(0);
 
     // Layout per il contenuto ALL'INTERNO del frame
    auto *frameContentLayout = new QVBoxLayout(m_cardFrame); 
    frameContentLayout->setContentsMargins(8, 8, 8, 8); 
    frameContentLayout->setSpacing(5);
    frameContentLayout->setAlignment(Qt::AlignTop );

    m_coverLabel = new QLabel();
    m_coverLabel->setFixedSize(164, 240);
    m_coverLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_coverLabel->setStyleSheet("background-color: transparent;"); 

    m_titleLabel = new QLabel(QString::fromStdString(m_content->getTitle()));
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setAlignment(Qt::AlignCenter| Qt::AlignHCenter);
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 14px; background-color: transparent");


    m_yearLabel = new QLabel(QString::number(m_content->getYear()));
    m_yearLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    m_statusLayout = new QHBoxLayout();
    m_statusLayout->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_statusLayout->setSpacing(10); 

    // Add elements to card
    frameContentLayout->addWidget(m_coverLabel);
    frameContentLayout->addWidget(m_titleLabel);
    frameContentLayout->addWidget(m_yearLabel);
    frameContentLayout->addLayout(m_statusLayout);

    cardLayout->addWidget(m_cardFrame);


    // Set cover image
    auto coverPath = QString::fromStdString(m_content->getImage());
    if (!coverPath.isEmpty() && QFile::exists(coverPath)) {
        m_coverLabel->setPixmap(QPixmap(coverPath).scaled(m_coverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_coverLabel->setAlignment(Qt::AlignCenter);
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
        m_cardFrame->setStyleSheet("QFrame#ContentCardFrame { border: 2px solid #39FF14; border-radius: 5px; }");
    } else if (m_content->getStarred() && m_content->getWatched()) {
        m_cardFrame->setStyleSheet("QFrame#ContentCardFrame { border: 2px solid #BC13FE; border-radius: 5px; }");
    } else if (m_content->getStarred()) {
        m_cardFrame->setStyleSheet("QFrame#ContentCardFrame { border: 2px solid #CFFF04; border-radius: 5px; }");
    } else if (m_content->getWatched()) {
        m_cardFrame->setStyleSheet("QFrame#ContentCardFrame { border: 2px solid rgb(0, 182, 30); border-radius: 5px; }");
    } else {
        m_cardFrame->setStyleSheet("QFrame#ContentCardFrame { border: 1px solid #ccc; border-radius: 5px; }");
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