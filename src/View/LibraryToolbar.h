#ifndef LIBRARYTOOLBAR_H
#define LIBRARYTOOLBAR_H

#include <QToolBar>
#include <QToolButton>
#include <QMenu>

class LibraryToolbar : public QToolBar {
    Q_OBJECT
public:
    explicit LibraryToolbar(QWidget *parent = nullptr);

signals:
    void importRequested();
    void saveRequested(const QString &extension);

private:
    void setupToolbar();
    void createSaveMenu();
    void createImportButton();
    
    QToolButton *m_importButton = nullptr;
    QToolButton *m_saveButton = nullptr;
    QMenu *m_saveMenu = nullptr;
};

#endif // LIBRARYTOOLBAR_H