#include "SortingSectionWidget.h"
#include <type_traits> // For std::underlying_type_t

using std::underlying_type_t;

SortingSectionWidget::SortingSectionWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    connect(m_sortingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SortingSectionWidget::onSortComboBoxIndexChanged);
    connect(m_sortDirectionButton, &QToolButton::clicked, this, &SortingSectionWidget::onSortDirectionButtonClicked);

    // Emit initial sort state
    onSortComboBoxIndexChanged(m_sortingComboBox->currentIndex());
}

void SortingSectionWidget::setupUI() {
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(new QLabel("Sort by:"));

    auto *sortControlsLayout = new QHBoxLayout();
    m_sortingComboBox = new QComboBox();
    m_sortingComboBox->setToolTip("Sort by");
    m_sortingComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_sortingComboBox->setMinimumWidth(120);
    m_sortingComboBox->addItem("Title", static_cast<underlying_type_t<ContentModel::SortRole>>(ContentModel::SortRole::Title));
    m_sortingComboBox->addItem("Year", static_cast<underlying_type_t<ContentModel::SortRole>>(ContentModel::SortRole::Year));
    m_sortingComboBox->addItem("Creator", static_cast<underlying_type_t<ContentModel::SortRole>>(ContentModel::SortRole::Creator));
    m_sortingComboBox->addItem("Type", static_cast<underlying_type_t<ContentModel::SortRole>>(ContentModel::SortRole::Type));
    sortControlsLayout->addWidget(m_sortingComboBox);

    m_sortDirectionButton = new QToolButton();
    m_sortDirectionButton->setIcon(QIcon(":assets/icons/ord-cresc.png"));
    m_sortDirectionButton->setIconSize(QSize(28, 28));
    m_sortDirectionButton->setCheckable(true);
    m_sortDirectionButton->setToolTip("Sort Ascending/Descending");
    sortControlsLayout->addWidget(m_sortDirectionButton);

    sortControlsLayout->addStretch();
    layout->addLayout(sortControlsLayout);
}

void SortingSectionWidget::onSortComboBoxIndexChanged(int index) {
    int role = m_sortingComboBox->itemData(index).toInt();
    emit sortCriteriaChanged(static_cast<ContentModel::SortRole>(role), m_currentSortOrder);
}

void SortingSectionWidget::onSortDirectionButtonClicked() {
    m_currentSortOrder = m_sortDirectionButton->isChecked() ? Qt::DescendingOrder : Qt::AscendingOrder;
    m_sortDirectionButton->setIcon(QIcon(m_currentSortOrder == Qt::AscendingOrder ? ":assets/icons/ord-cresc.png" : ":assets/icons/ord-decresc.png"));

    onSortComboBoxIndexChanged(m_sortingComboBox->currentIndex()); // Re-emit with new direction
}

ContentModel::SortRole SortingSectionWidget::getCurrentSortRole() const {
    return static_cast<ContentModel::SortRole>(m_sortingComboBox->currentData().toInt());
}

Qt::SortOrder SortingSectionWidget::getCurrentSortOrder() const {
    return m_currentSortOrder;
}