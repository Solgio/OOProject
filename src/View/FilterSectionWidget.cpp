#include "FilterSectionWidget.h"
#include "ContentProxyModel.h" 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMap>
#include <QStyle>
#include <type_traits> 

using std::underlying_type_t;

FilterSectionWidget::FilterSectionWidget(ContentProxyModel *proxyModel, QWidget *parent)
    : QWidget(parent), m_proxyModel(proxyModel) {
    setupUI();
    connect(m_filtersToggleBtn, &QToolButton::clicked, this, &FilterSectionWidget::onToggleFiltersClicked);
    connect(m_clearFiltersBtn, &QPushButton::clicked, this, &FilterSectionWidget::clearAllFiltersUI);
    }

void FilterSectionWidget::setupUI() {
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(5);

    // Initialize filter toggle button
    m_filtersToggleBtn = new QToolButton();
    m_filtersToggleBtn->setText("Filters");
    m_filtersToggleBtn->setCheckable(true);
    m_filtersToggleBtn->setToolTip("Show/Hide filters");
    mainLayout->addWidget(m_filtersToggleBtn);

    m_filtersStackedWidget = new QStackedWidget();

    // Compact widget
    m_compactFiltersWidget = createCompactFilterWidget();
    m_filtersStackedWidget->addWidget(m_compactFiltersWidget); // Index 0
    m_filtersStackedWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    // Expanded section - now using a scroll area directly
    m_filtersScrollArea = new QScrollArea();
    m_filtersScrollArea->setWidgetResizable(true);
    m_filtersScrollArea->setFrameShape(QFrame::NoFrame);
    m_filtersScrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);


    // Container widget for filters
    m_expandedFiltersSection = new QWidget();
    auto *filtersLayout = new QVBoxLayout(m_expandedFiltersSection);
    filtersLayout->setContentsMargins(5, 5, 5, 5);
    filtersLayout->setSpacing(10); // Increased spacing between groups
    m_expandedFiltersSection->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    // Style sheets (unchanged)
    QString checkboxStyle =
        "QCheckBox:checked {"
        "   border: 2px solid #39FF14;"
        "   border-radius: 3px;"
        "   padding: 2px;"
        "}"
        "QCheckBox:hover {"
        "   background-color:rgb(85, 87, 86);"
        "}"
        "QCheckBox:checked:hover {"
        "   background-color:rgb(0, 110, 59);"
        "}";
    QString radioButtonStyle =
        "QRadioButton:checked {"
        "   border: 2px solid #39FF14;"
        "   border-radius: 3px;"
        "   padding: 2px;"
        "}"
        "QRadioButton:hover {"
        "   background-color:rgb(85, 87, 86);"
        "}"
        "QRadioButton:checked:hover {"
        "   background-color:rgb(0, 110, 59);"
        "}";

    // Type filter section
    auto *typeGroup = new QGroupBox("Content Types");
    typeGroup->setFlat(true);
    typeGroup->setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 3px; margin-top: 6px; }");
    typeGroup->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    auto *typeLayout = new QVBoxLayout(typeGroup);
    typeLayout->setContentsMargins(5, 15, 5, 5);
    typeLayout->setSpacing(5);

    QStringList types = {"Book", "Comic", "Film", "Serie", "VideoGame"};
    for (const QString &type : types) {
        auto *rb = new QRadioButton(type);
        rb->setProperty("filterType", "type");
        rb->setProperty("filterValue", type);
        rb->setStyleSheet(radioButtonStyle);
        connect(rb, &QRadioButton::clicked, this, [this, rb]() {
            QString currentFilter = m_proxyModel->getTypeFilter();
            if (currentFilter == rb->text()) {
                rb->setAutoExclusive(false);
                rb->setChecked(false);
                rb->setAutoExclusive(true);
                m_proxyModel->clearTypeFilter();
            } else {
                m_proxyModel->setTypeFilter(rb->text());
            }
            onFilterRadioButtonClicked();
        });
        typeLayout->addWidget(rb);
        m_filterControls["type"].append(rb);
    }
    filtersLayout->addWidget(typeGroup);

    // Genre filter section - now with better size management
    auto *genreGroup = new QGroupBox("Genres");
    genreGroup->setFlat(true);
    genreGroup->setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 3px; margin-top: 6px; }");
    genreGroup->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    auto *genreLayout = new QVBoxLayout(genreGroup);
    genreLayout->setContentsMargins(5, 15, 5, 5);
    genreLayout->setSpacing(5);

    // Genre map setup (unchanged)
    QMap<int, QString> genreMap;
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::NONE)] = "None";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::ACTION)] = "Action";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::ADVENTURE)] = "Adventure";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::COMEDY)] = "Comedy";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::DRAMA)] = "Drama";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::HORROR)] = "Horror";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::ROMANCE)] = "Romance";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::THRILLER)] = "Thriller";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::MYSTERY)] = "Mystery";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::WESTERN)] = "Western";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::WAR)] = "War";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::MUSICAL)] = "Musical";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::FAMILY)] = "Family";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::SPORTS)] = "Sports";
    genreMap[static_cast<underlying_type_t<Subgenre>>(Subgenre::SUPERHERO)] = "Superhero";

    // Create a scroll area just for genres if they don't fit
    auto *genreScrollArea = new QScrollArea();
    genreScrollArea->setWidgetResizable(true);
    genreScrollArea->setFrameShape(QFrame::NoFrame);
    genreScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    auto *genreContainer = new QWidget();
    auto *genreContainerLayout = new QVBoxLayout(genreContainer);
    genreContainerLayout->setContentsMargins(0, 0, 0, 0);
    genreContainerLayout->setSpacing(5);

    for (auto it = genreMap.begin(); it != genreMap.end(); ++it) {
        auto *cb = new QCheckBox(it.value());
        cb->setProperty("filterType", "genre");
        cb->setProperty("filterValue", it.key());
        cb->setStyleSheet(checkboxStyle);
        connect(cb, &QCheckBox::stateChanged, this, &FilterSectionWidget::onFilterCheckboxStateChanged);
        genreContainerLayout->addWidget(cb);
        m_filterControls["genre"].append(cb);
    }
    
    genreScrollArea->setWidget(genreContainer);
    genreLayout->addWidget(genreScrollArea);
    filtersLayout->addWidget(genreGroup);

    // Status filters
    auto *statusGroup = new QGroupBox("Status");
    statusGroup->setFlat(true);
    statusGroup->setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 3px; margin-top: 6px; }");
    statusGroup->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    auto *statusLayout = new QVBoxLayout(statusGroup);
    statusLayout->setContentsMargins(5, 15, 5, 5);
    statusLayout->setSpacing(5);

    auto *watchedCb = new QCheckBox("Watched Only");
    watchedCb->setProperty("filterType", "watched");
    watchedCb->setStyleSheet(checkboxStyle);
    connect(watchedCb, &QCheckBox::stateChanged, this, &FilterSectionWidget::onFilterCheckboxStateChanged);
    statusLayout->addWidget(watchedCb);
    m_filterControls["watched"].append(watchedCb);

    auto *starredCb = new QCheckBox("Starred Only");
    starredCb->setProperty("filterType", "starred");
    starredCb->setStyleSheet(checkboxStyle);
    connect(starredCb, &QCheckBox::stateChanged, this, &FilterSectionWidget::onFilterCheckboxStateChanged);
    statusLayout->addWidget(starredCb);
    m_filterControls["starred"].append(starredCb);
    filtersLayout->addWidget(statusGroup);

    // Clear button and counter
    auto *bottomRow = new QWidget();
    auto *bottomLayout = new QHBoxLayout(bottomRow);
    bottomLayout->setContentsMargins(0, 0, 0, 0);

    m_clearFiltersBtn = new QPushButton("Clear All");
    m_clearFiltersBtn->setMaximumWidth(80);
    bottomLayout->addWidget(m_clearFiltersBtn);

    m_filterCounter = new QLabel("0 items");
    bottomLayout->addWidget(m_filterCounter);
    bottomLayout->addStretch();
    filtersLayout->addWidget(bottomRow);

    // Set up the scroll area
    m_filtersScrollArea->setWidget(m_expandedFiltersSection);
    m_filtersStackedWidget->addWidget(m_filtersScrollArea); // Index 1

    mainLayout->addWidget(m_filtersStackedWidget);
    mainLayout->setStretch(1, 1);
}

QWidget* FilterSectionWidget::createCompactFilterWidget() {
    auto *compactWidget = new QWidget();
    compactWidget->setMaximumHeight(40);
    auto *layout = new QHBoxLayout(compactWidget);
    layout->setContentsMargins(5, 5, 5, 5);

    // Reuse m_filterCounter from expanded view, or create a new one
    // For simplicity here, we'll assume m_filterCounter is already created in setupUI
    // and just add it to this layout. The parent will be changed.
    m_filterCounter = new QLabel("0 items"); // Re-initialize for compact view if needed
    m_filterCounter->setAlignment(Qt::AlignRight);

    layout->addStretch();
    layout->addWidget(m_filterCounter);

    compactWidget->setCursor(Qt::PointingHandCursor);
    compactWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    return compactWidget;
}

void FilterSectionWidget::onToggleFiltersClicked() {
    m_isExpanded = !m_isExpanded;
    m_filtersStackedWidget->setCurrentIndex(m_isExpanded ? 1 : 0);
    m_filtersToggleBtn->setChecked(m_isExpanded);
    emit toggleExpanded(m_isExpanded);
}

void FilterSectionWidget::onFilterCheckboxStateChanged() {
    applyInternalFilters();
    emit filtersChanged();
}

void FilterSectionWidget::onFilterRadioButtonClicked() {
    applyInternalFilters();
    emit filtersChanged();
}

void FilterSectionWidget::applyInternalFilters() {
    if (!m_proxyModel) return;

    // Clear existing type and genre filters in proxy model before re-applying
    m_proxyModel->clearTypeFilter();
    m_proxyModel->clearSubgenreFilter();
    m_proxyModel->setWatchedFilter(false);
    m_proxyModel->setStarredFilter(false);

    // Apply type filter
    for (QAbstractButton *button : m_filterControls["type"]) {
        QRadioButton *rb = qobject_cast<QRadioButton*>(button);
        if (rb && rb->isChecked()) {
            m_proxyModel->setTypeFilter(rb->text());
            break; // Only one type can be selected
        }
    }

    // Apply genre filters
    for (QAbstractButton *button : m_filterControls["genre"]) {
        QCheckBox *cb = qobject_cast<QCheckBox*>(button);
        if (cb && cb->isChecked()) {
            int genreValue = cb->property("filterValue").toInt();
            m_proxyModel->setSubgenreFilter(static_cast<Subgenre>(genreValue));
        }
    }

    // Apply status filters
    for (QAbstractButton *button : m_filterControls["watched"]) {
        QCheckBox *cb = qobject_cast<QCheckBox*>(button);
        if (cb && cb->isChecked()) {
            m_proxyModel->setWatchedFilter(true);
        }
    }
    for (QAbstractButton *button : m_filterControls["starred"]) {
        QCheckBox *cb = qobject_cast<QCheckBox*>(button);
        if (cb && cb->isChecked()) {
            m_proxyModel->setStarredFilter(true);
        }
    }
    emit filtersChanged();
}

void FilterSectionWidget::updateFilterCounter(int count) {
    m_filterCounter->setText(QString("%1 item%2").arg(count).arg(count == 1 ? "" : "s"));
}

void FilterSectionWidget::clearAllFiltersUI() {
    // Clear all checkboxes
    for (const auto& key : m_filterControls.keys()) {
        for (QAbstractButton *button : m_filterControls[key]) {
            button->blockSignals(true);
            if (QCheckBox *cb = qobject_cast<QCheckBox*>(button)) {
                cb->setChecked(false);
            } else if (QRadioButton *rb = qobject_cast<QRadioButton*>(button)) {
                rb->setAutoExclusive(false);
                rb->setChecked(false);
                rb->setAutoExclusive(true);
            }
            button->blockSignals(false);
        }
    }
    // Re-apply filters to clear them in the proxy model as well
    applyInternalFilters();
    emit clearFiltersRequested();
}

void FilterSectionWidget::updateToggleButtonState(bool hasActiveFilters) {
    if(!m_filtersToggleBtn) return; // Ensure the button is initialized

    if (hasActiveFilters) {
        m_filtersToggleBtn->setText("Filters (Active)");
        m_filtersToggleBtn->setStyleSheet("QToolButton {border: 1px solid #39FF14; }");
    } else {
        m_filtersToggleBtn->setText("Filters");
        m_filtersToggleBtn->setStyleSheet("");
    }
}