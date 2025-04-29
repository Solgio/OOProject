#ifndef LIBRARYWINDOW_H
#define LIBRARYWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QListWidgetItem>
#include <QSplitter>
#include <QCheckBox>
#include <QPushButton>
#include <QMap>
#include <QTableView>
#include <QGridLayout>
#include <QScrollArea>
#include <QComboBox>
#include "../Model/lib/ScienceFictionLibrary.h"

class QListWidget;
class QLabel;
class QLineEdit;
class QComboBox;
class QMenu;
class ContentDetailWindow;
class QTimer;
class ContentModel;
class ContentProxyModel;

class LibraryWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LibraryWindow(QWidget *parent = nullptr);
    ~LibraryWindow() override;
    bool eventFilter(QObject* obj, QEvent* event) override;

signals:
    void contentDataChanged();

private slots:
    void importContent();
    void saveToFile(const QString &extension);
    void updateContentDisplay();
    void showContentDetails(const QModelIndex &index);

    void showAddContentDialog(bool checked = false);
    void editContent(Content* content = nullptr);

    void hideDetailView();
    void applySearchFilter(const QString &text);

    void applyFilters();
    void clearFilters();
    void clearSearch();
    
    void delayedSearch();
    void updateFilterCounter();
    void changeSortDirection();

private:
    //              ==== UI Setup ====
    void setupUI();
    void setupContentTable();
    void setupFilterSection();
    void setupToolbar();
    void setupPreviewWidget();
    void setupSortingControls();

    // New method to create compact filter widget
    QWidget* createCompactFilterWidget();
    
    void connectSignals();
    
    // Helper methods
    void createSaveMenu();
    void createImportButton();
    void toggleFiltersSection();
    void updateContentPreviews();
    QWidget* createContentPreviewCard(Content* content);
    void updateFilterToggleButtonState();

    // UI Components
    QToolBar *m_toolBar = nullptr;
    QSplitter *m_splitter = nullptr;
    QTableView *m_contentTable = nullptr;
    QLineEdit *m_searchBar = nullptr;
    QToolButton *m_importButton = nullptr;
    QToolButton *m_saveButton = nullptr;
    QToolButton *m_add = nullptr;
    QToolButton *m_clearSearchButton = nullptr;
    QMenu *m_saveMenu = nullptr;
    ContentDetailWindow *m_detailWindow = nullptr;
    QTimer *m_searchTimer = nullptr;

    // Models
    ContentModel *m_contentModel = nullptr;
    ContentProxyModel *m_proxyModel = nullptr;
    
    // Filters
    QWidget* m_filtersSection = nullptr;
    QToolButton* m_filtersToggleBtn = nullptr;
    QPushButton* m_clearFiltersBtn = nullptr;
    QLabel* m_filterCounter = nullptr;
    QScrollArea* m_filtersScrollArea = nullptr;
    
    // New filter-related members
    QWidget* m_compactFiltersWidget = nullptr;
    QStackedWidget* m_filtersStackedWidget = nullptr;
    bool m_filtersExpanded = false;

    QLayout* m_sortingLayout = nullptr;

    // Sorting controls
    QComboBox* m_sortingComboBox = nullptr;
    QToolButton* m_sortDirectionButton = nullptr;

    // Content preview widgets
    QWidget* m_previewWidget = nullptr;
    QScrollArea* m_previewScrollArea = nullptr;
    QGridLayout* m_previewLayout = nullptr;

    // Stacked widgets
    QStackedWidget *m_rightPanel = nullptr;
    QStackedWidget *m_contentContainer = nullptr;
    QWidget *m_mainView = nullptr;
    QLabel *m_noResultsLabel = nullptr;

    // Selected Content
    QWidget* m_selectedCard = nullptr;

    const int SEARCH_DELAY_MS = 350;
};

#endif // LIBRARYWINDOW_H