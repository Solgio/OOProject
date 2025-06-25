#include "ShortcutManager.h"
#include <QShortcut>
#include <QLineEdit>
#include "ContentDetailWindow.h" // For back to main view

ShortcutManager::ShortcutManager(QObject *parent) : QObject(parent) {}

void ShortcutManager::setupShortcuts(
    QObject* targetParent,
    QLineEdit* searchBar
) {
    // Add content shortcut (Ctrl+N)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), targetParent, SIGNAL(addContentShortcut()));

    // Import content shortcut (Ctrl+I)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_I), targetParent, SIGNAL(importContentShortcut()));

    // Save JSON shortcut (Ctrl+S)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), targetParent, SIGNAL(saveJsonShortcut()));

    // Save XML shortcut (Ctrl+Shift+S)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S), targetParent, SIGNAL(saveXmlShortcut()));

    // Toggle filters shortcut (Ctrl+F)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), targetParent, SIGNAL(toggleFiltersShortcut()));

    // Reverse changes in Edit Window (Ctrl+Z)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), targetParent, SIGNAL(editWindowReverseChanges()));

    // Focus search bar shortcut (Ctrl+K or Alt+S)
    auto *focusSearchShortcut1 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_K), searchBar);
    connect(focusSearchShortcut1, &QShortcut::activated, searchBar, QOverload<>::of(&QLineEdit::setFocus));
    auto *focusSearchShortcut2 = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_S), searchBar);
    connect(focusSearchShortcut2, &QShortcut::activated, searchBar, QOverload<>::of(&QLineEdit::setFocus));

    // Clear search shortcut (Esc when search has focus) - ONLY for search bar
    auto *clearSearchShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), searchBar);
    clearSearchShortcut->setContext(Qt::WidgetShortcut); // Only when search bar has focus
    connect(clearSearchShortcut, &QShortcut::activated, this, &ShortcutManager::clearSearchShortcut);


    // Clear all filters shortcut (Ctrl+Shift+F)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_F), targetParent, SIGNAL(clearFiltersShortcut()));

    // Return to main view from detail view (Esc)
    auto *escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), qobject_cast<QWidget*>(targetParent));
    escShortcut->setContext(Qt::ApplicationShortcut); // or Qt::WindowShortcut
    connect(escShortcut, &QShortcut::activated, this, &ShortcutManager::backToMainViewShortcut);

    
    // Change sort direction shortcut (Ctrl+D)
    createAndConnectShortcut(QKeySequence(Qt::CTRL | Qt::Key_D), targetParent, SIGNAL(changeSortDirectionShortcut()));

    // Refresh/update content display (F5)
    createAndConnectShortcut(QKeySequence(Qt::Key_F5), targetParent, SIGNAL(refreshContentShortcut()));
}

void ShortcutManager::createAndConnectShortcut(const QKeySequence &sequence, QObject *parent, const char *signal) {
    auto *shortcut = new QShortcut(sequence, qobject_cast<QWidget*>(parent));
    if (shortcut) {
        connect(shortcut, SIGNAL(activated()), this, signal);
    }
}