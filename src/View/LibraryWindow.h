#ifndef LIBRARYWINDOW_H
#define LIBRARYWINDOW_H

#include "ContentModel.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QStackedWidget>
#include <QSplitter>
#include <QTimer>
#include <QVBoxLayout>

// Forward declarations for new classes
class LibraryToolbar;
class FilterSectionWidget;
class SortingSectionWidget;
class ContentPreviewGrid;
class LibraryActionsManager;
class ShortcutManager;
class ContentDetailWindow;
class ContentProxyModel;
class Content; // For editContent slot
class ContentEditWindow; // For editContent slot

class LibraryWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LibraryWindow(QWidget *parent = nullptr);
    ~LibraryWindow() override = default;

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    // Slots for actions from Toolbar or Shortcuts
    void handleImportRequested();
    void handleSaveRequested(const QString &extension);
    void handleAddContentRequested();
    void handleEditContent(Content* content = nullptr);

    // Slots for search
    void delayedSearch();
    void applySearchFilter();
    void clearSearch();

    // Slots for filter/sort changes
    void handleFiltersChanged();
    void handleClearFiltersRequested();
    void handleSortCriteriaChanged(ContentModel::SortRole role, Qt::SortOrder order);

    // Slot for updating content display
    void updateContentDisplay();

    // Slot for detail view
    void hideDetailView();
    void hideEditView(int pastIndex = 0);

    // Slot for ContentPreviewGrid interactions
    void showDetailView(Content* content);
    void showEditView(Content* content);

private:
    // UI Setup methods
    void setupUI();
    void createLeftPanel(QWidget* parentWidget);
    void createRightPanel();
    void createAddButton();
    void connectSignals();

    // Helper to update overall filter state (including search)
    void updateOverallFilterState();

    // Override for unsaved changes purpose
    void closeEvent(QCloseEvent *event) override;

    bool unsavedContent = false; // Track if there are unsaved changes

    // UI Components (now instances of new classes or simpler widgets)
    LibraryToolbar *m_toolBar = nullptr;
    QSplitter *m_splitter = nullptr;
    QLineEdit *m_searchBar = nullptr;
    QToolButton *m_clearSearchButton = nullptr;

    FilterSectionWidget *m_filterSectionWidget = nullptr;
    SortingSectionWidget *m_sortingSectionWidget = nullptr;
    ContentPreviewGrid *m_contentPreviewGrid = nullptr;

    QStackedWidget *m_rightPanel = nullptr;
    QToolButton *m_addContentButton = nullptr;
    ContentDetailWindow *m_detailWindow = nullptr;
    ContentEditWindow *m_editWindow = nullptr;

    // Models
    ContentModel *m_contentModel = nullptr;
    ContentProxyModel *m_proxyModel = nullptr;

    // Managers
    LibraryActionsManager *m_actionsManager = nullptr;
    ShortcutManager *m_shortcutManager = nullptr;

    QTimer *m_searchTimer = nullptr;
    const int SEARCH_DELAY_MS = 350;
};

#endif // LIBRARYWINDOW_H