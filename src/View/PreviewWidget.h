#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QListWidgetItem>
#include "../Model/lib/Content.h"

class PreviewWidget : public QListWidgetItem {
public:
    explicit PreviewWidget(Content* content, QListWidget *parent = nullptr);
    void updatePreview(const QSize &size);
    Content* getContent() const;

private:
    Content* m_content;
    QPixmap loadPixmap(const QString &path, const QSize &size) const;
};

#endif