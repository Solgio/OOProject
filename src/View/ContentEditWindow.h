#ifndef CONTENTEDITWINDOW_H
#define CONTENTEDITWINDOW_H

#include <QDialog>
#include "../Model/lib/Content.h"

class QLineEdit;
class QSpinBox;
class QComboBox;
class QCheckBox;
class QTextEdit;
class QPushButton;
class QLabel;

class QVBoxLayout;
class CommonEditWindow;
class EditVisitor;

class ContentEditWindow : public QDialog {
    Q_OBJECT

public:
    explicit ContentEditWindow(Content* content, QWidget *parent = nullptr);
    ~ContentEditWindow() override = default;

signals:
    void contentUpdated();

private slots:
    void saveChanges();

private:
    void setupUI();
    void updateEditWindow();

    Content* m_content;
    EditVisitor *editVis;
    // UI Components
    /*
    QLabel *m_typeLabel;
    QLineEdit *m_titleEdit;
    QSpinBox *m_yearSpin;
    QList<QCheckBox*> m_subgenreCheckboxes;
    QWidget *m_subgenreContainer;
    QCheckBox *m_watchedCheck;
    QCheckBox *m_starredCheck;
    QTextEdit *m_descEdit;
    QLineEdit *m_imagePathEdit;
    */
    QVBoxLayout *mainLayout;

    CommonEditWindow *contentEditWindow;

    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    QPushButton *m_browseButton;
};

#endif
