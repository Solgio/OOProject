#ifndef CONTENTPREVIEWGRID_H
#define CONTENTPREVIEWGRID_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QMap>

class ContentProxyModel;
class Content;
class ContentCardWidget;

class ContentPreviewGrid : public QWidget {
    Q_OBJECT

public:
    explicit ContentPreviewGrid(ContentProxyModel *proxyModel, QWidget *parent = nullptr);
    void updatePreviews();
    void selectCard(Content* content);
    void deselectCurrentCard();

signals:
    void contentDoubleClicked(Content* content);
    void contentSingleClicked(Content* content);

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void handleCardDoubleClick(Content* content);
    void handleCardSingleClick(Content* content);

private:
    ContentProxyModel *m_proxyModel;
    QScrollArea *m_previewScrollArea = nullptr;
    QWidget *m_previewWidget = nullptr;
    QGridLayout *m_previewLayout = nullptr;
    QLabel *m_noResultsLabel = nullptr;

    ContentCardWidget *m_selectedCardWidget = nullptr;
    QMap<Content*, ContentCardWidget*> m_contentToCardMap; // To easily find cards by content pointer
};

#endif // CONTENTPREVIEWGRID_H