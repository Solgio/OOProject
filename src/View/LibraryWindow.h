#ifndef LIBRARYWINDOW_H
#define LIBRARYWINDOW_H

#include <QMainWindow>
#include "../Model/lib/ScienceFictionLibrary.h"
#include <QListWidgetItem>
#include <QSplitter>
#include <QToolButton>

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

private slots:
    void importContent();
    void saveToFile(const QString &extension);
    void updateContentDisplay();
    void showContentDetails(QListWidgetItem *item);
    void editContentTriggered(bool checked = false);
    void editContent(Content* content = nullptr);
    void hideDetailView();

private:
    void setupUI();
    void connectSignals() const;
    void loadContentPreview(Content* content, QListWidgetItem* item) const;
    QPixmap loadSafePixmap(const QString &path, const QSize &size) const;
    void verifyResources() const;
    void createSaveMenu();
    void createImportButton();

    // UI Components
    QToolBar *m_toolBar = nullptr;
    QWidget *m_centralWidget = nullptr;
    QSplitter *m_splitter = nullptr;
    QListWidget *m_contentList = nullptr;
    QLineEdit *m_searchBar = nullptr;
    QComboBox *m_filterCombo = nullptr;
    QToolButton *m_importButton = nullptr;
    QToolButton *m_saveButton = nullptr;
    QMenu *m_saveMenu = nullptr;
    ContentDetailWindow *m_detailWindow = nullptr;
    QWidget *m_rightPanel = nullptr;
    QToolButton *m_add = nullptr;

    const QSize m_previewSize{120, 180};
};

#endif