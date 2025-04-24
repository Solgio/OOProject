#ifndef LIBRARYWINDOW_H
#define LIBRARYWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QListWidgetItem>
#include <QSplitter>
#include "../Model/lib/ScienceFictionLibrary.h"


class QListWidget;
class QLabel;
class QLineEdit;
class QComboBox;
class QMenu;
class ContentDetailWindow;

class LibraryWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LibraryWindow(QWidget *parent = nullptr);
    ~LibraryWindow() override;

    bool isSearchBarEmpty() const { return m_searchBar->text().isEmpty(); }

private slots:
    void importContent();
    void saveToFile(const QString &extension);
    void updateContentDisplay();
    void showContentDetails(QListWidgetItem *item);
    void editContentTriggered(bool checked = false);
    void editContent(Content* content = nullptr);
    void hideDetailView();
    void onFilterChanged(int index);

private:
    void setupUI();
    void connectSignals();
    void createToolbar();
    void createSaveMenu();
    void createImportButton();
    void loadContentPreview(Content* content, QListWidgetItem* item) const;
    QPixmap loadSafePixmap(const QString &path, const QSize &size) const;
    void verifyResources() const;

    // UI Components
    QToolBar *m_toolBar = nullptr;
    QSplitter *m_splitter = nullptr;
    QListWidget *m_contentList = nullptr;
    QLineEdit *m_searchBar = nullptr;
    QComboBox *m_filterCombo = nullptr;
    QToolButton *m_importButton = nullptr;
    QToolButton *m_saveButton = nullptr;
    QToolButton *m_add = nullptr;
    QMenu *m_saveMenu = nullptr;
    ContentDetailWindow *m_detailWindow = nullptr;
    
    // Stacked widgets
    QStackedWidget *m_rightPanel = nullptr;
    QStackedWidget *m_contentContainer = nullptr;
    //QStackedWidget *m_noResultsContainer = nullptr; !DUTURE UPDATE WITH no-results.png icon
    QWidget *m_mainView = nullptr;
    QLabel *m_noResultsLabel = nullptr;

    const QSize m_previewSize{120, 180};
};

#endif