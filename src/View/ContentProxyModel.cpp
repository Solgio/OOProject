#include "ContentProxyModel.h"
#include "../Model/lib/Content.h"
#include <QMetaType>

ContentProxyModel::ContentProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      m_filterWatched(false),
      m_filterStarred(false),
      m_sortRole(ContentModel::SortRole::Title) {
    
    // Enable dynamic sorting
    setDynamicSortFilter(true);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    
    // Set initial sort
    sort(0, Qt::AscendingOrder);
}

void ContentProxyModel::setTitleFilter(const QString &title) {
    m_titleFilter = title;
    invalidateFilter();
}

void ContentProxyModel::setTypeFilter(const QString &type) {
    if (!m_typeFilters.contains(type)) {
        m_typeFilters.append(type);
        invalidateFilter();
    }
}

void ContentProxyModel::removeTypeFilter(const QString &type) {
    if (m_typeFilters.contains(type)) {
        m_typeFilters.removeAll(type);
        invalidateFilter();
    }
}

void ContentProxyModel::setSubgenreFilter(Subgenre subgenre) {
    if (!m_subgenreFilters.contains(subgenre)) {
        m_subgenreFilters.append(subgenre);
        invalidateFilter();
    }
}

void ContentProxyModel::removeSubgenreFilter(Subgenre subgenre) {
    if (m_subgenreFilters.contains(subgenre)) {
        m_subgenreFilters.removeAll(subgenre);
        invalidateFilter();
    }
}

void ContentProxyModel::setWatchedFilter(bool watched) {
    m_filterWatched = watched;
    invalidateFilter();
}

void ContentProxyModel::setStarredFilter(bool starred) {
    m_filterStarred = starred;
    invalidateFilter();
}

void ContentProxyModel::clearFilters() {
    m_titleFilter.clear();
    m_typeFilters.clear();
    m_subgenreFilters.clear();
    m_filterWatched = false;
    m_filterStarred = false;
    invalidateFilter();
}

void ContentProxyModel::setSortRole(ContentModel::SortRole role) {
    m_sortRole = role;
    invalidate();
    sort(0, sortOrder());
}

bool ContentProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    
    // Get the Content pointer
    auto* contentModel = qobject_cast<ContentModel*>(sourceModel());
    if (!contentModel)
        return false;
        
    Content* content = contentModel->getContent(sourceRow);
    if (!content)
        return false;
    
    // Apply title filter
    if (!m_titleFilter.isEmpty()) {
        auto title = QString::fromStdString(content->getTitle());
        if (!title.contains(m_titleFilter, Qt::CaseInsensitive))
            return false;
    }
    
    // Apply type filter
    //!Todo TO BE CHANGED, CANNOT USE GETTYPE
    if (!m_typeFilters.isEmpty()) {
        auto type = QString::fromStdString(content->getType());
        if (!m_typeFilters.contains(type))
            return false;
    }
    
    // Apply subgenre filter
    if (!m_subgenreFilters.isEmpty()) {
        auto subgenre = static_cast<Subgenre>(content->getSubgenre());
        // Check if content has ALL selected subgenres (AND condition)
        for (Subgenre filter : m_subgenreFilters) {
            if (!content->hasSubgenre(filter)){  // Changed from == to !=
                return false;
            }
        }
    }
    
    // Apply watched filter
    if (m_filterWatched && !content->getWatched())
        return false;
    
    // Apply starred filter
    if (m_filterStarred && !content->getStarred())
        return false;
    
    return true;
}

bool ContentProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const {
    ContentModel* contentModel = qobject_cast<ContentModel*>(sourceModel());
    if (!contentModel)
        return QSortFilterProxyModel::lessThan(source_left, source_right);
    
    Content* leftContent = contentModel->getContent(source_left.row());
    Content* rightContent = contentModel->getContent(source_right.row());
    
    if (!leftContent || !rightContent)
        return QSortFilterProxyModel::lessThan(source_left, source_right);
    
    // Use the ContentModel method to get the sort value based on the current sort role
    QVariant leftValue = contentModel->getSortValue(leftContent, m_sortRole);
    QVariant rightValue = contentModel->getSortValue(rightContent, m_sortRole);
    
    // Handle special comparisons based on type
    if (leftValue.typeId() == QVariant::String && rightValue.typeId() == QVariant::String) {
        return QString::localeAwareCompare(leftValue.toString(), rightValue.toString()) < 0;
    } else if (leftValue.typeId() == QMetaType::Int && rightValue.typeId() == QMetaType::Int) {
        return leftValue.toInt() < rightValue.toInt();
    } else if (leftValue.typeId() == QMetaType::Double && rightValue.typeId() == QMetaType::Double) {
        return leftValue.toDouble() < rightValue.toDouble();
    } else if (leftValue.typeId() == QMetaType::Int && rightValue.typeId() == QMetaType::Int) {
        return leftValue.toInt() < rightValue.toInt();
    }
    
    // Default comparison
    return QSortFilterProxyModel::lessThan(source_left, source_right);
}
