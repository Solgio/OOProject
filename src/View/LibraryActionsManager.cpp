#include "LibraryActionsManager.h"
#include "../Model/lib/ScienceFictionLibrary.h" // Assuming this path
#include "../Model/lib/Content.h"               // Assuming this path
#include "TypeChoiceDialog.h"                   // Assuming this path
#include "ContentEditWindow.h"                  // Assuming this path

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

LibraryActionsManager::LibraryActionsManager(QWidget *parent) : QObject(parent), m_parentWidget(parent) {}

void LibraryActionsManager::importContent()
{
    

    QString file = QFileDialog::getOpenFileName(
        m_parentWidget,
        "Import Content",
        QDir::homePath(),
        "Supported Files (*.xml *.json)");

    if (!file.isEmpty())
    {
        try{
            bool success = ScienceFiction_Library::getInstance().loadFromFile(file.toStdString());
            if (success)
            {
                QMessageBox::information(m_parentWidget, "Success", "Content imported successfully");
                emit contentDataChanged(); // Notify that data has changed
            }
            else
            {
                QMessageBox::warning(m_parentWidget, "Error", "Failed to import content");
            }
        }catch(IncorrectPrequelSequelLoading&){
            QMessageBox::warning(m_parentWidget, "Error", "Sequel or prequel loaded incorrectly");
        }
        
    }
}

void LibraryActionsManager::saveToFile(const QString &extension)
{
    QString file = QFileDialog::getSaveFileName(
        m_parentWidget,
        QString("Save As %1").arg(extension.toUpper()),
        QDir::homePath(),
        QString("%1 Files (*.%1)").arg(extension));

    if (!file.isEmpty())
    {
        bool success = ScienceFiction_Library::getInstance().saveToFile(file.toStdString());
        if (success)
        {
            QMessageBox::information(m_parentWidget, "Success", "Library saved successfully");
            emit contentSaved();
        }
        else
        {
            QMessageBox::warning(m_parentWidget, "Error", "Failed to save library");
        }
    }
}

void LibraryActionsManager::showAddContentDialog()
{
    TypeChoiceDialog typeDialog(m_parentWidget);
    if (typeDialog.exec() == QDialog::Accepted)
    {
        Content *newContent = typeDialog.createSelectedContent();
        if (newContent)
        {
            // Assign a new ID before editing
            newContent->setId(ScienceFiction_Library::getInstance().getNewId());
            // Then go to edit window for details
            editContent(newContent);
        }
    }
}

void LibraryActionsManager::editContent(Content *content)
{
    if (!content)
        return;
    emit editContentRequested(content);
}
