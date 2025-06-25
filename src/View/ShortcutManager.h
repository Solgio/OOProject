#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H

#include <QObject>
#include <QKeySequence>

class QLineEdit;
class ContentDetailWindow; // Forward declare if needed

class ShortcutManager : public QObject {
    Q_OBJECT

public:
    explicit ShortcutManager(QObject *parent = nullptr);

    void setupShortcuts(
        QObject* targetParent, // Usually LibraryWindow
        QLineEdit* searchBar
    );

signals:
    void addContentShortcut();
    void importContentShortcut();
    void saveJsonShortcut();
    void saveXmlShortcut();
    void toggleFiltersShortcut();
    void clearSearchShortcut();
    void clearFiltersShortcut();
    void backToMainViewShortcut();
    void changeSortDirectionShortcut();
    void editWindowReverseChanges();
    void refreshContentShortcut();

private:
    void createAndConnectShortcut(const QKeySequence &sequence, QObject *parent, const char *signal);
};

#endif // SHORTCUTMANAGER_H