#include "ContentPreviewGrid.h"
#include "ContentProxyModel.h" // Assuming this path
#include "ContentCardWidget.h" // Assuming this path
#include <QResizeEvent>
#include <QTimer>
#include <algorithm> // For std::max

ContentPreviewGrid::ContentPreviewGrid(ContentProxyModel *proxyModel, QWidget *parent)
    : QWidget(parent), m_proxyModel(proxyModel), m_previewScrollArea(new QScrollArea()), m_previewWidget(new QWidget()), m_noResultsLabel(new QLabel())
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    m_previewScrollArea->setWidgetResizable(true);
    m_previewScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_previewScrollArea->setFrameShape(QFrame::NoFrame);

    m_previewLayout = new QGridLayout(m_previewWidget);
    m_previewLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_previewLayout->setSpacing(10);
    m_previewLayout->setContentsMargins(5, 5, 5, 5);

    m_noResultsLabel->setPixmap(QPixmap(":assets/icons/no-results.png"));
    m_noResultsLabel->setAlignment(Qt::AlignCenter);
    m_noResultsLabel->setText("<center><h2 style='color:gray;'>No results found</h2></center>");
    m_noResultsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_noResultsLabel->hide();

    m_previewLayout->addWidget(m_noResultsLabel, 0, 0, 1, 6); // Span all columns by default
    m_previewScrollArea->setWidget(m_previewWidget);
    mainLayout->addWidget(m_previewScrollArea);

    // Connect to proxy model changes to update previews
    connect(m_proxyModel, &QAbstractItemModel::layoutChanged, this, &ContentPreviewGrid::updatePreviews);
    connect(m_proxyModel, &QAbstractItemModel::modelReset, this, &ContentPreviewGrid::updatePreviews);
}

void ContentPreviewGrid::updatePreviews()
{
    // Before clearing, check if the currently selected card is still present
    // in the *new* filtered list from the proxy model.
    // We don't call filterAcceptsRow directly. Instead, we iterate the proxy model's data.
    Content *previouslySelectedContent = nullptr;
    if (m_selectedCardWidget)
    {
        previouslySelectedContent = m_selectedCardWidget->getContent();
    }

    // Clear existing layout (except for no results label)
    QLayoutItem *item;
    QList<QWidget *> widgetsToDelete;
    while ((item = m_previewLayout->takeAt(0)) != nullptr)
    {
        if (item->widget() != m_noResultsLabel)
        {
            widgetsToDelete.append(item->widget());
            delete item;
        }
    }
    // Delete widgets outside the loop to avoid iterator invalidation
    for (QWidget *w : widgetsToDelete)
    {
        m_contentToCardMap.remove(static_cast<ContentCardWidget *>(w)->getContent());
        delete w;
    }
    // Add the no results label back to the layout (it might have been removed)
    m_previewLayout->addWidget(m_noResultsLabel, 0, 0, 1, 6);

    int count = m_proxyModel->rowCount();
    m_noResultsLabel->setVisible(count == 0);

    if (count == 0)
    {
        // If no results, deselect any previously selected card
        deselectCurrentCard();
        return;
    }

    const int CARD_WIDTH = 190; // Fixed card width + spacing
    int availableWidth = m_previewScrollArea->viewport()->width();
    int columns = std::max(1, availableWidth / CARD_WIDTH);

    bool wasSelectedContentStillVisible = false; // Flag to track if the selected content is still in the filtered list

    if (m_selectedCardWidget)
    {                                                                   // Assuming m_selectedCardWidget is the QWidget* selected card
        previouslySelectedContent = m_selectedCardWidget->getContent(); // Assuming ContentCardWidget::getContent() exists
    }

    int row = 0, col = 0;
    for (int i = 0; i < count; ++i)
    {
        QModelIndex proxyIndex = m_proxyModel->index(i, 0);
        if (!proxyIndex.isValid())
            continue;

        ContentModel *contentModel = qobject_cast<ContentModel *>(m_proxyModel->sourceModel());
        if (!contentModel)
        {
            // Gestire l'errore o continuare
            continue;
        }
        QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);
        Content *content = contentModel->getContent(sourceIndex.row());

        if (content)
        {
            ContentCardWidget *card = new ContentCardWidget(content);
            card->setStyleSheet("QWidget#ContentCard { border: 2px solid #FF0000; border-radius: 5px; background-color: transparent; }");
            m_contentToCardMap.insert(content, card);
            connect(card, &ContentCardWidget::doubleClicked, this, &ContentPreviewGrid::handleCardDoubleClick);
            connect(card, &ContentCardWidget::singleClicked, this, &ContentPreviewGrid::handleCardSingleClick);

            if (previouslySelectedContent && previouslySelectedContent == content)
            {
                card->setSelected(true);
                m_selectedCardWidget = card; // Update reference to new widget instance
                wasSelectedContentStillVisible = true;
            }

            m_previewLayout->addWidget(card, row, col);
            col++;
            if (col >= columns)
            {
                col = 0;
                row++;
            }
        }
    }

    // If the previously selected content is no longer in the filtered list, deselect it.
    if (previouslySelectedContent && !wasSelectedContentStillVisible)
    {
        deselectCurrentCard();
    }
}

void ContentPreviewGrid::handleCardDoubleClick(Content *content)
{
    emit contentDoubleClicked(content);
}

void ContentPreviewGrid::handleCardSingleClick(Content *content)
{
    if (m_selectedCardWidget)
    {
        if (m_selectedCardWidget->getContent() == content)
        {
            // Deselect if already selected
            deselectCurrentCard();
            return;
        }
        else
        {
            m_selectedCardWidget->setSelected(false);
        }
    }
    m_selectedCardWidget = m_contentToCardMap.value(content, nullptr);
    if (m_selectedCardWidget)
    {
        m_selectedCardWidget->setSelected(true);
    }
    emit contentSingleClicked(content);
}

void ContentPreviewGrid::selectCard(Content *content)
{
    deselectCurrentCard();
    m_selectedCardWidget = m_contentToCardMap.value(content, nullptr);
    if (m_selectedCardWidget)
    {
        m_selectedCardWidget->setSelected(true);
    }
}

void ContentPreviewGrid::deselectCurrentCard()
{
    if (m_selectedCardWidget)
    {
        m_selectedCardWidget->setSelected(false);
        m_selectedCardWidget = nullptr;
    }
}

void ContentPreviewGrid::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    static QTimer *resizeTimer = nullptr;
    if (!resizeTimer)
    {
        resizeTimer = new QTimer(this);
        resizeTimer->setSingleShot(true);
        connect(resizeTimer, &QTimer::timeout, this, &ContentPreviewGrid::updatePreviews);
    }
    resizeTimer->start(150);
}