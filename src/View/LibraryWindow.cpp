#include "LibraryWindow.h"
#include "LibraryToolbar.h"
#include "FilterSectionWidget.h"
#include "SortingSectionWidget.h"
#include "ContentPreviewGrid.h"
#include "LibraryActionsManager.h"
#include "ShortcutManager.h"
#include "ContentDetailWindow.h"
#include "ContentModel.h"
#include "ContentProxyModel.h"
#include "ContentEditWindow.h"

#include "../Model/lib/ScienceFictionLibrary.h" // For getInstance()
#include "../Model/lib/Content.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QEvent>

LibraryWindow::LibraryWindow(QWidget *parent) : QMainWindow(parent)
{
    // Initialize models first
    m_contentModel = new ContentModel(this);
    m_proxyModel = new ContentProxyModel(this);
    m_proxyModel->setSourceModel(m_contentModel);

    // Initialize managers
    m_actionsManager = new LibraryActionsManager(this);
    m_shortcutManager = new ShortcutManager(this);

    // Initialize search timer
    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);
    m_searchTimer->setInterval(SEARCH_DELAY_MS);

    setupUI();
    connectSignals();
    updateContentDisplay(); // Initial display
}

LibraryWindow::~LibraryWindow()
{
    // Child widgets and models are parented to this, so they will be deleted automatically.
    // Explicit deletes only for non-parented or dynamically allocated objects if any.
}

void LibraryWindow::setupUI()
{
    setWindowTitle("Science Fiction Library Manager");
    resize(1920, 1080);

    // Main splitter
    m_splitter = new QSplitter(Qt::Horizontal);
    setCentralWidget(m_splitter);

    // Toolbar (now an instance of LibraryToolbar)
    m_toolBar = new LibraryToolbar(this);
    addToolBar(m_toolBar);

    // Left Panel
    auto *leftPanel = new QWidget();
    createLeftPanel(leftPanel);
    m_splitter->addWidget(leftPanel);

    // Right Panel
    createRightPanel();
    m_splitter->addWidget(m_rightPanel);

    m_splitter->setStretchFactor(0, 1); // Left panel gets minimal space
    m_splitter->setStretchFactor(1, 4); // Right panel gets 4x more space
}

void LibraryWindow::createLeftPanel(QWidget *parentWidget)
{
    auto *leftLayout = new QVBoxLayout(parentWidget);
    leftLayout->setContentsMargins(5, 5, 5, 5);

    // Search bar with clear button
    auto *searchContainer = new QWidget();
    auto *searchLayout = new QHBoxLayout(searchContainer);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(5);

    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search content...");
    m_clearSearchButton = new QToolButton();
    m_clearSearchButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    m_clearSearchButton->setCursor(Qt::PointingHandCursor);
    m_clearSearchButton->setToolTip("Clear search");
    m_clearSearchButton->hide(); // Hidden initially

    searchLayout->addWidget(m_searchBar);
    searchLayout->addWidget(m_clearSearchButton);
    leftLayout->addWidget(searchContainer);

    // Filter section (now an instance of FilterSectionWidget)
    m_filterSectionWidget = new FilterSectionWidget(m_proxyModel);
    leftLayout->addWidget(m_filterSectionWidget);

    // Sorting controls (now an instance of SortingSectionWidget)
    m_sortingSectionWidget = new SortingSectionWidget();
    leftLayout->addWidget(m_sortingSectionWidget);
}

void LibraryWindow::createRightPanel()
{
    m_rightPanel = new QStackedWidget();

    // Main view (contains content preview grid)
    auto *mainView = new QWidget();
    auto *mainViewLayout = new QVBoxLayout(mainView);
    mainViewLayout->setContentsMargins(0, 0, 0, 0);

    mainViewLayout->addWidget(new QLabel("Content Library:"));

    // Content preview grid (now an instance of ContentPreviewGrid)
    m_contentPreviewGrid = new ContentPreviewGrid(m_proxyModel);
    mainViewLayout->addWidget(m_contentPreviewGrid);

    m_rightPanel->addWidget(mainView); // Index 0

    auto *buttonContainer = new QWidget();
    auto *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(0, 0, 10, 10);
    buttonLayout->addStretch();
    createAddButton();
    buttonLayout->addWidget(m_addContentButton);
    mainViewLayout->addWidget(buttonContainer);

    // Detail window
    m_detailWindow = new ContentDetailWindow(this);
    m_rightPanel->addWidget(m_detailWindow); // Index 1

    m_editWindow = nullptr;

}

void LibraryWindow::createAddButton() {
    m_addContentButton = new QToolButton();
    m_addContentButton->setText("Add Content");
    m_addContentButton->setIcon(QIcon(":assets/icons/add.png"));
    m_addContentButton->setToolTip("Add new content to the library");
    m_addContentButton->setFixedSize(QSize(40, 40));
    m_addContentButton->setIconSize(QSize(32, 32));
    connect(m_addContentButton, &QToolButton::clicked, this, &LibraryWindow::handleAddContentRequested);
}

void LibraryWindow::connectSignals()
{
    // Connect LibraryToolbar signals to LibraryActionsManager slots
    connect(m_toolBar, &LibraryToolbar::importRequested, m_actionsManager, &LibraryActionsManager::importContent);
    connect(m_toolBar, &LibraryToolbar::saveRequested, m_actionsManager, &LibraryActionsManager::saveToFile);
    //connect(m_toolBar, &LibraryToolbar::addContentRequested, m_actionsManager, &LibraryActionsManager::showAddContentDialog);

    // Connect LibraryActionsManager signals to LibraryWindow slots for UI updates
    connect(m_actionsManager, &LibraryActionsManager::contentDataChanged, this, &LibraryWindow::updateContentDisplay);
    connect(m_actionsManager, &LibraryActionsManager::contentEdited, m_detailWindow, &ContentDetailWindow::refreshContent);

    // Connect FilterSectionWidget signals
    connect(m_filterSectionWidget, &FilterSectionWidget::filtersChanged, this, &LibraryWindow::handleFiltersChanged);
    connect(m_filterSectionWidget, &FilterSectionWidget::clearFiltersRequested, this, &LibraryWindow::handleClearFiltersRequested);

    // Connect SortingSectionWidget signals
    connect(m_sortingSectionWidget, &SortingSectionWidget::sortCriteriaChanged, this, &LibraryWindow::handleSortCriteriaChanged);

    // Connect search bar signals
    connect(m_searchBar, &QLineEdit::textChanged, this, &LibraryWindow::delayedSearch);
    connect(m_searchTimer, &QTimer::timeout, this, &LibraryWindow::applySearchFilter);
    connect(m_clearSearchButton, &QToolButton::clicked, this, &LibraryWindow::clearSearch);
    connect(m_searchBar, &QLineEdit::textChanged, this, [this](const QString &text)
            { m_clearSearchButton->setVisible(!text.isEmpty()); });

    // Connect ContentDetailWindow signals
    // Used when a new object is created
    connect(m_actionsManager, &LibraryActionsManager::editContentRequested,  this, &LibraryWindow::showEditView);
    // Used when an existing object is edited
    connect(m_detailWindow, &ContentDetailWindow::editRequested, this, &LibraryWindow::showEditView);
    //
    connect(m_detailWindow, &ContentDetailWindow::closeRequested, this, &LibraryWindow::hideDetailView);
    connect(m_detailWindow, &ContentDetailWindow::contentDeleted, this, &LibraryWindow::updateContentDisplay);

    // Connect ContentPreviewGrid signals
    connect(m_contentPreviewGrid, &ContentPreviewGrid::contentDoubleClicked, this, &LibraryWindow::showDetailView);

    // Setup and connect shortcuts
    m_shortcutManager->setupShortcuts(this, m_searchBar, m_detailWindow);
    connect(m_shortcutManager, &ShortcutManager::addContentShortcut, this, &LibraryWindow::handleAddContentRequested);
    connect(m_shortcutManager, &ShortcutManager::importContentShortcut, this, &LibraryWindow::handleImportRequested);
    connect(m_shortcutManager, &ShortcutManager::saveJsonShortcut, this, [this]()
            { handleSaveRequested("json"); });
    connect(m_shortcutManager, &ShortcutManager::saveXmlShortcut, this, [this]()
            { handleSaveRequested("xml"); });
    connect(m_shortcutManager, &ShortcutManager::toggleFiltersShortcut, m_filterSectionWidget, &FilterSectionWidget::onToggleFiltersClicked); // Directly toggle
    connect(m_shortcutManager, &ShortcutManager::clearSearchShortcut, this, &LibraryWindow::clearSearch);
    connect(m_shortcutManager, &ShortcutManager::clearFiltersShortcut, m_filterSectionWidget, &FilterSectionWidget::clearAllFiltersUI);
    connect(m_shortcutManager, &ShortcutManager::backToMainViewShortcut, this, [this] () 
            { if(m_rightPanel->currentIndex()==0) return;
              else if(m_rightPanel->currentIndex()==1) hideDetailView();
              else if(m_rightPanel->currentIndex()==2) m_editWindow->cancelChanges(); });
    connect(m_shortcutManager, &ShortcutManager::editWindowReverseChanges, this, [this] ()
            { if(m_rightPanel->currentIndex()==2) m_editWindow->restoreChanges(); });
    connect(m_shortcutManager, &ShortcutManager::changeSortDirectionShortcut, m_sortingSectionWidget, &SortingSectionWidget::onSortDirectionButtonClicked);
    connect(m_shortcutManager, &ShortcutManager::refreshContentShortcut, this, &LibraryWindow::updateContentDisplay);
    //connect(m_shortcutManager, &ShortcutManager::backToMainViewShortcutActivated, this, &LibraryWindow::hideDetailView);


    // Connect ContentProxyModel signals to ContentPreviewGrid for updates
    connect(m_proxyModel, &ContentProxyModel::layoutChanged, m_contentPreviewGrid, &ContentPreviewGrid::updatePreviews);
    connect(m_proxyModel, &ContentProxyModel::modelReset, m_contentPreviewGrid, &ContentPreviewGrid::updatePreviews);
    connect(m_proxyModel, &ContentProxyModel::rowsInserted, m_contentPreviewGrid, &ContentPreviewGrid::updatePreviews);
    connect(m_proxyModel, &ContentProxyModel::rowsRemoved, m_contentPreviewGrid, &ContentPreviewGrid::updatePreviews);

    // Splitter resize for updating content previews
    connect(m_splitter, &QSplitter::splitterMoved, this, [this]()
            {
        static QTimer *splitterTimer = nullptr;
        if (!splitterTimer) {
            splitterTimer = new QTimer(this);
            splitterTimer->setSingleShot(true);
            connect(splitterTimer, &QTimer::timeout, m_contentPreviewGrid, &ContentPreviewGrid::updatePreviews);
        }
        splitterTimer->start(200); });
}

void LibraryWindow::handleImportRequested()
{
    m_actionsManager->importContent();
    if(m_rightPanel->currentIndex() != 0) // If we are in main view, update immediately
    {
        if(m_rightPanel->currentIndex() == 2) // If we are in detail view, refresh content
        {
            hideEditView();
        }
        hideDetailView();
    }
}

void LibraryWindow::handleSaveRequested(const QString &extension)
{
    m_actionsManager->saveToFile(extension);
}

void LibraryWindow::handleAddContentRequested()
{
    m_actionsManager->showAddContentDialog();
}

void LibraryWindow::handleEditContent(Content *content)
{
    m_actionsManager->editContent(content);
}

void LibraryWindow::delayedSearch()
{
    m_searchTimer->start();
}

void LibraryWindow::applySearchFilter()
{
    if(m_rightPanel->currentIndex() != 0) // If we are in main view, update immediately
    {
        if(m_rightPanel->currentIndex() == 2) // If we are in detail view, refresh content
        {
            hideEditView();
        }
        hideDetailView();
    }
    m_proxyModel->setTitleFilter(m_searchBar->text());
    // updateContentPreviews() is called by m_proxyModel::layoutChanged signal
    updateOverallFilterState();
}

void LibraryWindow::clearSearch()
{
    m_searchBar->clear();
    applySearchFilter(); // This will also hide the clear button and update overall filter state
}

void LibraryWindow::handleFiltersChanged()
{
    // applyInternalFilters() is called within FilterSectionWidget
    // We just need to trigger a preview update and filter state update
    if(m_rightPanel->currentIndex() != 0) // If we are in main view, update immediately
    {
        if(m_rightPanel->currentIndex() == 2) // If we are in detail view, refresh content
        {
            hideEditView();
        }
        hideDetailView();
    }
    updateOverallFilterState();
}

void LibraryWindow::handleClearFiltersRequested()
{
    clearSearch();                // Clear search as well for "clear all"
    m_proxyModel->clearFilters(); // Clear proxy model filters
    updateOverallFilterState();   // Update filter counter and button state
}

void LibraryWindow::handleSortCriteriaChanged(ContentModel::SortRole role, Qt::SortOrder order)
{
    m_proxyModel->setSortRole(role);
    m_proxyModel->sort(0, order);
    // updateContentPreviews() is called by m_proxyModel::layoutChanged signal
}

void LibraryWindow::updateContentDisplay()
{
    m_contentModel->refreshData(); // Re-fetch all data from ScienceFiction_Library
    // m_proxyModel will notify its view (ContentPreviewGrid)
    updateOverallFilterState(); // Update filter counter and button state
}

void LibraryWindow::hideDetailView()
{
    m_rightPanel->setCurrentIndex(0); // Show main view
}

void LibraryWindow::showDetailView(Content *content)
{
    if (content)
    {
        m_detailWindow->setContent(content);
        m_rightPanel->setCurrentIndex(1); // Show detail view
    }
}

void LibraryWindow::showEditView(Content *content)
{
    if (!content)
        return;

    // Clean up existing edit window if it exists
    if (m_editWindow) {
        disconnect(m_editWindow, nullptr, this, nullptr); // Disconnect all signals
        m_rightPanel->removeWidget(m_editWindow);
        m_editWindow->setParent(nullptr);
        m_editWindow->deleteLater();
        m_editWindow = nullptr;
    }

    // Create new edit window for this content
    m_editWindow = new ContentEditWindow(content, this);
    
    // Connect signals for this specific edit window
    connect(m_editWindow, &ContentEditWindow::contentUpdated, this, [this, content]() {
        auto &library = ScienceFiction_Library::getInstance();
        
        // Check if this is a new content or existing one
        bool isNew = true;
        for (const auto &existingContent : library.getContentList()) {
            if (existingContent.get() == content) {
                isNew = false;
                break;
            }
        }

        if (isNew) {
            library.addContent(content); // Add new content
        }
        
        updateContentDisplay(); // Call directly instead of emit m_actionsManager->contentDataChanged()
        m_detailWindow->refreshContent();
        
        hideEditView(); // Go back to detail view
    });
    
    // Connect close signal here so no warning is shown. In fact, if this was with the others connect it would generatte a nullptr warning of qtcore
    connect(m_editWindow, &ContentEditWindow::closeRequested, this, [this, content]() {
        // If it's a new content that was canceled, we need to delete it
        bool isNew = true;
        auto &library = ScienceFiction_Library::getInstance();
        for (const auto &existingContent : library.getContentList()) {
            if (existingContent.get() == content) {
                isNew = false;
                break;
            }
        }

        if (isNew) {
            delete content; // Clean up unadded content
        }
        
        hideEditView(); // Go back to previous view
    });

    // Add edit window to stacked widget and show it
    int editIndex = m_rightPanel->addWidget(m_editWindow);
    m_editWindow->setContent(content);
    m_rightPanel->setCurrentIndex(editIndex);
}

void LibraryWindow::hideEditView()
{
    if (m_editWindow) {
        // Remove from stacked widget and delete it
        disconnect(m_editWindow, nullptr, this, nullptr);
        m_rightPanel->removeWidget(m_editWindow);
        m_editWindow->setParent(nullptr);
        m_editWindow->deleteLater();
        m_editWindow = nullptr;
    }
    if(m_detailWindow)
        m_rightPanel->setCurrentIndex(1); // Detail view
    else
        m_rightPanel->setCurrentIndex(0); // Main view
}

void LibraryWindow::updateOverallFilterState()
{
    // Check if there are any active filters (search bar, filter section)
    bool hasActiveFilters = !m_searchBar->text().isEmpty();

    // Check filters in FilterSectionWidget
    // This part requires FilterSectionWidget to expose its active filter state
    // For now, we can check the proxy model itself for active filters
    // Or, FilterSectionWidget could emit a signal with a boolean indicating active filters.
    // Let's assume for now that FilterSectionWidget updates its own toggle button state
    // and we only need to pass the search state to it.
    // A better approach would be to have FilterSectionWidget tell us if it has active filters.

    // A simpler way: if proxy model filters are active, then there are active filters.
    if (m_proxyModel->hasActiveFilters() || !m_searchBar->text().isEmpty())
    {
        hasActiveFilters = true;
    }
    else
    {
        hasActiveFilters = false;
    }

    m_filterSectionWidget->updateToggleButtonState(hasActiveFilters);
    m_filterSectionWidget->updateFilterCounter(m_proxyModel->rowCount());
}

void LibraryWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    // ContentPreviewGrid already listens to its own resize events (from scroll area's viewport)
    // and uses a timer, so no explicit call needed here unless for splitter resize.
}