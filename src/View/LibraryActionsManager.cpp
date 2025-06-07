#include "LibraryActionsManager.h"
#include "../Model/lib/ScienceFictionLibrary.h" // Assuming this path
#include "../Model/lib/Content.h"             // Assuming this path
#include "TypeChoiceDialog.h"                  // Assuming this path
#include "ContentEditWindow.h"                 // Assuming this path

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

LibraryActionsManager::LibraryActionsManager(QWidget *parent) : QObject(parent), m_parentWidget(parent) {}

void LibraryActionsManager::importContent() {
    QString file = QFileDialog::getOpenFileName(
        m_parentWidget,
        "Import Content",
        QDir::homePath(),
        "Supported Files (*.xml *.json)");

    if (!file.isEmpty()) {
        bool success = ScienceFiction_Library::getInstance().loadFromFile(file.toStdString());
        if (success) {
            QMessageBox::information(m_parentWidget, "Success", "Content imported successfully");
            emit contentDataChanged(); // Notify that data has changed
        } else {
            QMessageBox::warning(m_parentWidget, "Error", "Failed to import content");
        }
    }
}

void LibraryActionsManager::saveToFile(const QString &extension) {
    QString file = QFileDialog::getSaveFileName(
        m_parentWidget,
        QString("Save As %1").arg(extension.toUpper()),
        QDir::homePath(),
        QString("%1 Files (*.%1)").arg(extension));

    if (!file.isEmpty()) {
        bool success = ScienceFiction_Library::getInstance().saveToFile(file.toStdString());
        if (success) {
            QMessageBox::information(m_parentWidget, "Success", "Library saved successfully");
        } else {
            QMessageBox::warning(m_parentWidget, "Error", "Failed to save library");
        }
    }
}

void LibraryActionsManager::showAddContentDialog() {
    TypeChoiceDialog typeDialog(m_parentWidget);
    if (typeDialog.exec() == QDialog::Accepted) {
        Content *newContent = typeDialog.createSelectedContent();
        if (newContent) {
            // Assign a new ID before editing
            newContent->setId(ScienceFiction_Library::getInstance().getNewId());
            // Then go to edit window for details
            editContent(newContent);
        }
    }
}

void LibraryActionsManager::editContent(Content *content) {/*
    if (!content)
        return;

    ContentEditWindow editWindow(content, m_parentWidget);

    if (editWindow.exec() == QDialog::Accepted) {
        auto &library = ScienceFiction_Library::getInstance();

        // Check if this is a new content or existing one
        bool isNew = true;
        for (const auto &existingContent : library.getContentList()) {
            if (existingContent.get() == content) {
                isNew = false;
                break;
            }
        }

        if (isNew) {
            library.addContent(content); // Add new content
        }
        emit contentDataChanged(); // Notify that data has changed
        emit contentEdited(content); // Notify that specific content was edited
    } else if (content) {
        // If it's a new content that was canceled, we need to delete it
        bool isNew = true;
        auto &library = ScienceFiction_Library::getInstance();
        for (const auto &existingContent : library.getContentList()) {
            if (existingContent.get() == content) {
                isNew = false;
                break;
            }
        }

        if (isNew) {
            delete content; // Clean up unadded content
        }
    }
        */
}