#ifndef CONTENTCARDWIDGET_H
#define CONTENTCARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include "../Model/lib/Content.h" // Assuming this path

class ContentCardWidget : public QWidget {
    Q_OBJECT

public:
    explicit ContentCardWidget(Content *content, QWidget *parent = nullptr);
    Content* getContent() const { return m_content; }
    void setSelected(bool selected);
    void updateCardStyle();

signals:
    void doubleClicked(Content* content);
    void singleClicked(Content* content);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void setupUI();

    Content *m_content;
    bool m_isSelected = false;

    QFrame *m_cardFrame = nullptr;
    QLabel *m_coverLabel = nullptr;
    QLabel *m_titleLabel = nullptr;
    QLabel *m_typeLabel = nullptr;
    QLabel *m_genreLabel = nullptr;
    QLabel *m_yearLabel = nullptr;
    QHBoxLayout *m_statusLayout = nullptr;
};

#endif // CONTENTCARDWIDGET_H