#ifndef CONTENTDETAILWINDOW_H
#define CONTENTDETAILWINDOW_H

#include <QWidget>
#include "../Model/lib/Content.h"

class QLabel;
class QPushButton;
class QVBoxLayout;

class ContentDetailWindow : public QWidget {
    Q_OBJECT

public:
    explicit ContentDetailWindow(QWidget *parent = nullptr);
    void setContent(Content* content);

signals:
    void editRequested(Content* content);
    void closeRequested();
    void contentDeleted();

private slots:
    void onEditClicked();
    void onDeleteClicked();

public slots:
    void refreshContent();

private:
    void setupUI();
    void updateContentDisplay();
    
    Content* m_content;
    QLabel *m_contentDetails;
    QPushButton *m_editButton;
    QPushButton *m_deleteButton;
    QPushButton *m_closeButton;
    QVBoxLayout *m_mainLayout;
};

#endif