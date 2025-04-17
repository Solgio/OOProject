#include "PreviewWidget.h"
#include <QFile>

PreviewWidget::PreviewWidget(Content* content, QListWidget *parent)
    : QListWidgetItem(parent), m_content(content) {
    updatePreview(QSize(100, 150));
}

Content* PreviewWidget::getContent() const {
    return m_content;
}

void PreviewWidget::updatePreview(const QSize &size) {
    if (!m_content) return;
    
    setText(QString::fromStdString(m_content->getTitle()));
    setData(Qt::UserRole, QVariant(m_content->getId()));
    
    QPixmap pixmap = loadPixmap(
        QString::fromStdString(m_content->getImage()),
        size
    );
    setIcon(QIcon(pixmap));
}

QPixmap PreviewWidget::loadPixmap(const QString &path, const QSize &size) const {
    QPixmap pixmap;
    
    if (!path.isEmpty() && QFile::exists(path)) {
        pixmap.load(path);
    }
    
    if (pixmap.isNull()) {
        pixmap.load("assets/icons/default.png");
    }
    
    return pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}