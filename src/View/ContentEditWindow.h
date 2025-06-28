#ifndef CONTENTEDITWINDOW_H
#define CONTENTEDITWINDOW_H

#include <QDialog>
#include "../Model/lib/Content.h"
#include <QScrollArea>

class QLineEdit;
class QSpinBox;
class QComboBox;
class QCheckBox;
class QTextEdit;
class QPushButton;
class QLabel;
class QVBoxLayout;
class CommonEditWindow;
class Visitor;

class ContentEditWindow : public QWidget {
    Q_OBJECT

public:
    explicit ContentEditWindow(Content* content, QWidget *parent = nullptr);
    ~ContentEditWindow() override = default;
    void setContent(Content *content);
    void saveChanges();
    void cancelChanges();
    void restoreChanges();
    
signals:
    void contentUpdated();
    void closeRequested();

private:
    void setupUI();
    void updateEditWindow();

    Content* m_content;
    Visitor *editVis;

    QVBoxLayout *mainLayout;
    QScrollArea *scrollAreaForEditWindow;

    //contenitore per contentEditWindow perchè il setWidget di QScrollArea da Segmentation Fault nel updateEditWindow()
    //scrollWidget per contenere il Layout
    QWidget *scrollWidget;
    //contentEditLayout per contenere contentEditWindow/contentTypeEditWindow
    QVBoxLayout *contentEditLayout;

    CommonEditWindow *contentEditWindow = nullptr;
    CommonEditWindow *contentTypeEditWindow = nullptr;

    QPushButton *m_restoreButton;
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    QPushButton *m_browseButton;
};

#endif
