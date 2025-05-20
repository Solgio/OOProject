#ifndef SORTINGSECTIONWIDGET_H
#define SORTINGSECTIONWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QToolButton>
#include <QHBoxLayout>
#include <QLabel>

#include "ContentModel.h" // Assuming this path for SortRole

class SortingSectionWidget : public QWidget {
    Q_OBJECT

public:
    explicit SortingSectionWidget(QWidget *parent = nullptr);
    ContentModel::SortRole getCurrentSortRole() const;
    Qt::SortOrder getCurrentSortOrder() const;

signals:
    void sortCriteriaChanged(ContentModel::SortRole role, Qt::SortOrder order);

private slots:
    void onSortComboBoxIndexChanged(int index);
    void onSortDirectionButtonClicked();

private:
    void setupUI();

    QComboBox *m_sortingComboBox = nullptr;
    QToolButton *m_sortDirectionButton = nullptr;
    Qt::SortOrder m_currentSortOrder = Qt::AscendingOrder;
};

#endif // SORTINGSECTIONWIDGET_H