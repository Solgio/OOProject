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
#include "../Model/lib/ScienceFictionLibrary.h"

class QListWidget;
class QLabel;
class QLineEdit;
class QComboBox;
class QMenu;
class ContentDetailWindow;
class QTimer;

class LibraryWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LibraryWindow(QWidget *parent = nullptr);
    ~LibraryWindow() override;

    bool isSearchBarEmpty() const { return m_searchBar->text().isEmpty(); }

signals:
    void contentDataChanged();

private slots:
    void importContent();
    void saveToFile(const QString &extension);
    void updateContentDisplay();
    void showContentDetails(QListWidgetItem *item);

    void showAddContentDialog(bool checked = false);
    void editContent(Content* content = nullptr);

    void hideDetailView();
    void applyQuickFilter(int index);
    void delayedSearch();

    void applyFilters();
    void clearFilters();
    void clearSearch();

private:
    // UI Setup
    void setupUI();
    void setupContentListView();
    void setupFilterSection();
    void setupToolbar();
    void connectSignals();
    
    // Helper methods
    void createSaveMenu();
    void createImportButton();
    void loadContentPreview(Content* content, QListWidgetItem* item) const;
    QPixmap loadSafePixmap(const QString &path, const QSize &size) const;
    QListWidget* createFilterList(const QStringList& options);
    void toggleFiltersSection();

    // UI Components
    QToolBar *m_toolBar = nullptr;
    QSplitter *m_splitter = nullptr;
    QListWidget *m_contentList = nullptr;
    QLineEdit *m_searchBar = nullptr;
    QToolButton *m_importButton = nullptr;
    QToolButton *m_saveButton = nullptr;
    QToolButton *m_add = nullptr;
    QToolButton *m_clearSearchButton = nullptr;
    QMenu *m_saveMenu = nullptr;
    ContentDetailWindow *m_detailWindow = nullptr;
    QTimer *m_searchTimer = nullptr;

    // Filters
    QWidget* m_filtersSection = nullptr;
    QToolButton* m_filtersToggleBtn = nullptr;
    QListWidget* m_genreFilterList = nullptr;
    QListWidget* m_typeFilterList = nullptr;
    QListWidget* m_statusFilterList = nullptr;
    QPushButton* m_clearFiltersBtn = nullptr;
    QLabel* m_filterCounter = nullptr;

    // Stacked widgets
    QStackedWidget *m_rightPanel = nullptr;
    QStackedWidget *m_contentContainer = nullptr;
    QWidget *m_mainView = nullptr;
    QLabel *m_noResultsLabel = nullptr;

    const QSize m_previewSize{160, 240};
    const int SEARCH_DELAY_MS = 350;
};

#endif