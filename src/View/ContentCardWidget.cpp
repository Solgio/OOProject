#include "ContentCardWidget.h"
#include <QFile>
#include <QEvent>
#include <QVariant>

ContentCardWidget::ContentCardWidget(Content *content, QWidget *parent)
    : QWidget(parent), m_content(content), m_isSelected(false), m_cardFrame(nullptr) {
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
    //cardLayout->setContentsMargins(8, 8, 8, 8);
    //cardLayout->setSpacing(5);
    cardLayout->setAlignment(Qt::AlignTop );

    m_cardFrame = new QFrame();
    m_cardFrame->setObjectName("ContentCardFrame"); // Un objectName unico per il frame
    m_cardFrame->setFrameShape(QFrame::StyledPanel); // Può essere StyledPanel, Box, NoFrame, ecc.
    m_cardFrame->setFrameShadow(QFrame::Plain);      // Nessuna ombra per ora
    m_cardFrame->setLineWidth(0);                   // La larghezza del bordo sarà definita dallo stylesheet
    m_cardFrame->setMidLineWidth(0);
 
     // Layout per il contenuto ALL'INTERNO del frame
    auto *frameContentLayout = new QVBoxLayout(m_cardFrame); // Layout del frame
    frameContentLayout->setContentsMargins(8, 8, 8, 8); // Margini interni per il contenuto della card
    frameContentLayout->setSpacing(5);
    frameContentLayout->setAlignment(Qt::AlignTop );

    m_coverLabel = new QLabel();
    m_coverLabel->setFixedSize(164, 240);
    m_coverLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_coverLabel->setStyleSheet("background-color: transparent;"); // O un colore brillante

    m_titleLabel = new QLabel(QString::fromStdString(m_content->getTitle()));
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setAlignment(Qt::AlignCenter| Qt::AlignHCenter);
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    m_titleLabel->setStyleSheet("background-color: transparent");

/*
    m_typeLabel = new QLabel(QString::fromStdString(m_content->getType()));
    m_typeLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_typeLabel->setStyleSheet("background-color: transparent");

    m_genreLabel = new QLabel(QString::fromStdString(m_content->getSubgenreString()));
    m_genreLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_genreLabel->setStyleSheet("background-color: transparent");

    m_yearLabel = new QLabel(QString::number(m_content->getYear()));
    m_yearLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_genreLabel->setStyleSheet("background-color: transparent");
*/
    m_statusLayout = new QHBoxLayout();
    m_statusLayout->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_statusLayout->setSpacing(10); // Spacing between status labels

    // Add elements to card
    frameContentLayout->addWidget(m_coverLabel);
    frameContentLayout->addWidget(m_titleLabel);
    //frameContentLayout->addWidget(m_typeLabel);
    //frameContentLayout->addWidget(m_genreLabel);
    //frameContentLayout->addWidget(m_yearLabel);
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