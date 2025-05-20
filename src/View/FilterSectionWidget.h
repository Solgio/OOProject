#ifndef FILTERSECTIONWIDGET_H
#define FILTERSECTIONWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QScrollArea>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>

#include "../Model/lib/Content.h" // Per Subgenre enum
class ContentProxyModel;

class FilterSectionWidget : public QWidget {
    Q_OBJECT

public:
    explicit FilterSectionWidget(ContentProxyModel *proxyModel, QWidget *parent = nullptr);
    void updateFilterCounter(int count);
    void clearAllFiltersUI();
    void updateToggleButtonState(bool hasActiveFilters);

signals:
    void filtersChanged();
    void clearFiltersRequested();
    void toggleExpanded(bool expanded);

public slots:
    void onToggleFiltersClicked();

private slots:
    void onFilterCheckboxStateChanged();
    void onFilterRadioButtonClicked();

private:
    void setupUI();
    QWidget* createCompactFilterWidget();
    void applyInternalFilters();

    ContentProxyModel *m_proxyModel;

    QToolButton *m_filtersToggleBtn = nullptr;
    QPushButton *m_clearFiltersBtn = nullptr;
    QLabel *m_filterCounter = nullptr;
    QScrollArea *m_filtersScrollArea = nullptr;
    QWidget *m_compactFiltersWidget = nullptr;
    QStackedWidget *m_filtersStackedWidget = nullptr;
    QWidget *m_expandedFiltersSection = nullptr;

    bool m_isExpanded = false;

    // Store references to filter controls to manage their state
    QMap<QString, QList<QAbstractButton*>> m_filterControls;
};

#endif // FILTERSECTIONWIDGET_H