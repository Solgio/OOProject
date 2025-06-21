#include "ShortcutManager.h"
#include <QShortcut>
#include <QLineEdit>
#include "ContentDetailWindow.h" // For back to main view

ShortcutManager::ShortcutManager(QObject *parent) : QObject(parent) {}

void ShortcutManager::setupShortcuts(
    QObject* targetParent,
    QLineEdit* searchBar,
    ContentDetailWindow* detailWindow
) {
    // Add content shortcut (Ctrl+N)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), targetParent, SIGNAL(addContentShortcutActivated()));

    // Import content shortcut (Ctrl+I)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_I), targetParent, SIGNAL(importContentShortcutActivated()));

    // Save JSON shortcut (Ctrl+S)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), targetParent, SIGNAL(saveJsonShortcutActivated()));

    // Save XML shortcut (Ctrl+Shift+S)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S), targetParent, SIGNAL(saveXmlShortcutActivated()));

    // Toggle filters shortcut (Ctrl+F)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), targetParent, SIGNAL(toggleFiltersShortcutActivated()));

    // Reverse changes in Edit Window (Ctrl+Z)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), targetParent, SIGNAL(editWindowReverseChangesShortcutActivated()));

    // Focus search bar shortcut (Ctrl+K or Alt+S)
    auto *focusSearchShortcut1 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_K), searchBar);
    connect(focusSearchShortcut1, &QShortcut::activated, searchBar, QOverload<>::of(&QLineEdit::setFocus));
    auto *focusSearchShortcut2 = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_S), searchBar);
    connect(focusSearchShortcut2, &QShortcut::activated, searchBar, QOverload<>::of(&QLineEdit::setFocus));

    // Clear search shortcut (Esc when search has focus)
    auto *clearSearchShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), searchBar);
    connect(clearSearchShortcut, &QShortcut::activated, this, &ShortcutManager::clearSearchShortcutActivated);

    // Clear all filters shortcut (Ctrl+Shift+F)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_F), targetParent, SIGNAL(clearFiltersShortcutActivated()));

    // Return to main view from detail view (Esc)
    createAndConnectShortcut(QKeySequence(Qt::Key_Escape), targetParent, SIGNAL(backToMainViewShortcutActivated()));
    
    // Change sort direction shortcut (Ctrl+D)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_D), targetParent, SIGNAL(changeSortDirectionShortcutActivated()));

    // Refresh/update content display (F5)
    createAndConnectShortcut(QKeySequence(Qt::Key_F5), targetParent, SIGNAL(refreshContentShortcutActivated()));
}

void ShortcutManager::createAndConnectShortcut(const QKeySequence &sequence, QObject *parent, const char *signal) {
    auto *shortcut = new QShortcut(sequence, qobject_cast<QWidget*>(parent));
    if (shortcut) {
        connect(shortcut, SIGNAL(activated()), this, signal);
    }
}