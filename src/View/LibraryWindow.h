// LibraryWindow.h
#ifndef LIBRARY_WINDOW_H
#define LIBRARY_WINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>
#include <QSplitter>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include "../Model/lib/ScienceFictionLibrary.h"

class LibraryWindow : public QMainWindow {
    Q_OBJECT

public:
    LibraryWindow(QWidget *parent = nullptr);
    ~LibraryWindow();

private slots:
    void importContent();
    void saveAsXml();
    void saveAsJson();
    void searchContent(const QString &text);
    void filterContent(int index);
    void updateContentList();

private:
    void createToolBar();
    void createSidePanel();
    void createContentArea();
    void setupMainLayout();
    void connectActions();
    void refreshContentDisplay();

    // UI elements
    QAction *m_importAction;
    QAction *m_saveXmlAction;
    QAction *m_saveJsonAction;
    
    QWidget *m_sidePanel;
    QLineEdit *m_searchBar;
    QComboBox *m_filterCombo;
    QListWidget *m_contentList;
    
    QWidget *m_contentWidget;
    QLabel *m_contentDetails;
};
#endif