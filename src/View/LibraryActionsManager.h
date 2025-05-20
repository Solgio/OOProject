#ifndef LIBRARYACTIONSMANAGER_H
#define LIBRARYACTIONSMANAGER_H

#include <QObject>
#include <QString>

class Content;
class QWidget; // For parent in dialogs

class LibraryActionsManager : public QObject {
    Q_OBJECT

public:
    explicit LibraryActionsManager(QWidget *parent = nullptr);

public slots:
    void importContent();
    void saveToFile(const QString &extension);
    void showAddContentDialog();
    void editContent(Content* content = nullptr);

signals:
    void contentDataChanged();
    void contentEdited(Content* content); // Signal to update detail view
    void contentDeleted(); // When content is deleted through edit (not directly here)

private:
    QWidget *m_parentWidget; // To parent dialogs
};

#endif // LIBRARYACTIONSMANAGER_H