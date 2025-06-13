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

signals:
    void contentUpdated();
    void closeRequested();

private slots:
    void saveChanges();
    void cancelChanges();

private:
    void setupUI();
    void updateEditWindow();

    Content* m_content;
    Visitor *editVis;

    QVBoxLayout *mainLayout;
    QScrollArea *scrollAreaForEditWindow;

    CommonEditWindow *contentEditWindow;

    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    QPushButton *m_browseButton;
};

#endif
