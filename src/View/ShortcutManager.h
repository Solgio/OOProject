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
        QLineEdit* searchBar,
        ContentDetailWindow* detailWindow // For 'back to main view' shortcut
    );

signals:
    void addContentShortcutActivated();
    void importContentShortcutActivated();
    void saveJsonShortcutActivated();
    void saveXmlShortcutActivated();
    void toggleFiltersShortcutActivated();
    void clearSearchShortcutActivated();
    void clearFiltersShortcutActivated();
    void backToMainViewShortcutActivated();
    void changeSortDirectionShortcutActivated();
    void refreshContentShortcutActivated();

private:
    void createAndConnectShortcut(const QKeySequence &sequence, QObject *parent, const char *signal);
};

#endif // SHORTCUTMANAGER_H