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
class LibraryWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LibraryWindow(QWidget *parent = nullptr);
    ~LibraryWindow() override = default;

private slots:
    void importContent();
    void saveToFile(const QString &extension);
    void updateContentDisplay();
    void showContentDetails(QListWidgetItem *item);

private:
    void setupUI();
    void connectSignals();
    void loadContentPreview(Content* content, QListWidgetItem* item);
    QPixmap loadSafePixmap(const QString &path, const QSize &size) const;
    void verifyResources();
    void createSaveMenu();
    void createImportButton();

    // UI Components
    QToolBar *m_toolBar;
    QWidget *m_centralWidget;
    QSplitter *m_splitter;
    QListWidget *m_contentList;
    QLabel *m_contentDetails;
    QLineEdit *m_searchBar;
    QComboBox *m_filterCombo;
    QToolButton *m_importButton;
    QToolButton *m_saveButton;
    QMenu *m_saveMenu;

    const QSize m_previewSize{120, 180};
};

#endif