#include "ContentProxyModel.h"
#include "../Model/lib/Content.h"
#include "../Model/lib/Book.h"      // Include the definition of the Book class
#include "../Model/lib/Comic.h"     // Include the definition of the Comic class
#include "../Model/lib/Film.h"      // Include the definition of the ContentModel class
#include "../Model/lib/Serie.h"     // Include the definition of the Serie class
#include "../Model/lib/VideoGame.h" // Include the definition of the VideoGame class

#include <QMetaType>

ContentProxyModel::ContentProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      m_filterWatched(false),
      m_filterStarred(false),
      m_sortRole(ContentModel::SortRole::Title)
{

    // Enable dynamic sorting
    setDynamicSortFilter(true);
    setSortCaseSensitivity(Qt::CaseInsensitive);

    // Set initial sort
    sort(0, Qt::AscendingOrder);
}

void ContentProxyModel::setTitleFilter(const QString &title)
{
    m_titleFilter = title;
    invalidateFilter();
}

void ContentProxyModel::setTypeFilter(const QString &type)
{
    if (m_typeFilter != type)
    {
        m_typeFilter = type;
        invalidateFilter();
    }
}

void ContentProxyModel::clearTypeFilter()
{
    m_typeFilter.clear();
    invalidateFilter();
}
bool ContentProxyModel::hasActiveFilters() const{
    return !m_titleFilter.isEmpty() || !m_typeFilter.isEmpty() || !m_subgenreFilters.isEmpty() || m_filterWatched || m_filterStarred;
}

void ContentProxyModel::setSubgenreFilter(Subgenre subgenre)
{
    if (!m_subgenreFilters.contains(subgenre))
    {
        m_subgenreFilters.append(subgenre);
        invalidateFilter();
    }
}

void ContentProxyModel::clearSubgenreFilter()
{
    m_subgenreFilters.clear();
    invalidateFilter();
}

void ContentProxyModel::setWatchedFilter(bool watched)
{
    m_filterWatched = watched;
    invalidateFilter();
}

void ContentProxyModel::setStarredFilter(bool starred)
{
    m_filterStarred = starred;
    invalidateFilter();
}

void ContentProxyModel::clearFilters()
{
    m_titleFilter.clear();
    clearTypeFilter();
    m_subgenreFilters.clear();
    m_filterWatched = false;
    m_filterStarred = false;
    invalidateFilter();
}

void ContentProxyModel::setSortRole(ContentModel::SortRole role)
{
    m_sortRole = role;
    invalidate();
    sort(0, sortOrder());
}

bool ContentProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    ContentModel* contentModel = qobject_cast<ContentModel*>(sourceModel());
    if (!contentModel)
        return true; // Should not happen if sourceModel is correctly set

    Content* content = contentModel->getContent(sourceRow);
    if (!content)
        return false; // Invalid content

    // Apply title filter
    if (!m_titleFilter.isEmpty()) {
        if (!QString::fromStdString(content->getTitle()).contains(m_titleFilter, Qt::CaseInsensitive))
            return false;
    }

    // Apply type filter
    bool typeFilterApplied = false;
    if (!m_typeFilter.isEmpty()) {
        if (m_typeFilter == "Book") {
            typeFilterApplied = (dynamic_cast<Book*>(content)!=nullptr && !dynamic_cast<Comic*>(content));
        } else if (m_typeFilter == "Comic") {
            typeFilterApplied = (dynamic_cast<Comic*>(content)!=nullptr);
        } else if (m_typeFilter == "Film") {
           typeFilterApplied = (dynamic_cast<Film*>(content)!=nullptr);
        } else if (m_typeFilter == "Serie") {
            typeFilterApplied = (dynamic_cast<Serie*>(content)!=nullptr);
        } else if (m_typeFilter == "VideoGame") {
           typeFilterApplied = (dynamic_cast<VideoGame*>(content)!=nullptr);
        }
        if(!typeFilterApplied){
            return false;
        }
    }

    // Apply watched filter
    if (m_filterWatched) {
        if (!content->getWatched()) // Only show if watched
            return false;
    }

    // Apply starred filter
    if (m_filterStarred) {
        if (!content->getStarred()) // Only show if starred
            return false;
    }

    // Apply subgenre filters (if any are active)
     if (!m_subgenreFilters.isEmpty()) {
        // Check if content has ALL selected subgenres (AND condition)
        for (Subgenre filter : m_subgenreFilters) {
            if (!content->hasSubgenre(filter)){  
                return false;
            }
        }
    }

    return true; // Content passes all active filters
}


bool ContentProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    ContentModel *contentModel = qobject_cast<ContentModel *>(sourceModel());
    if (!contentModel)
        return QSortFilterProxyModel::lessThan(source_left, source_right);

    Content *leftContent = contentModel->getContent(source_left.row());
    Content *rightContent = contentModel->getContent(source_right.row());

    if (!leftContent || !rightContent)
        return QSortFilterProxyModel::lessThan(source_left, source_right);

    // Use the ContentModel method to get the sort value based on the current sort role
    QVariant leftValue = contentModel->getSortValue(leftContent, m_sortRole);
    QVariant rightValue = contentModel->getSortValue(rightContent, m_sortRole);

    // Handle special comparisons based on type
    if (leftValue.typeId() == QMetaType::QString && rightValue.typeId() == QMetaType::QString)
    {
        return QString::localeAwareCompare(leftValue.toString(), rightValue.toString()) < 0;
    }
    else if (leftValue.typeId() == QMetaType::Int && rightValue.typeId() == QMetaType::Int)
    {
        return leftValue.toInt() < rightValue.toInt();
    }
    else if (leftValue.typeId() == QMetaType::Double && rightValue.typeId() == QMetaType::Double)
    {
        return leftValue.toDouble() < rightValue.toDouble();
    }
    else if (leftValue.typeId() == QMetaType::Int && rightValue.typeId() == QMetaType::Int)
    {
        return leftValue.toInt() < rightValue.toInt();
    }

    // Default comparison
    return QSortFilterProxyModel::lessThan(source_left, source_right);
}
