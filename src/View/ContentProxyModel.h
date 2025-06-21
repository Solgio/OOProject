#ifndef CONTENTPROXYMODEL_H
#define CONTENTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "ContentModel.h"
#include "../Model/lib/Content.h"

class ContentProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
    
public:
    explicit ContentProxyModel(QObject *parent = nullptr);
    
    void setTitleFilter(const QString &title);
    void setTypeFilter(const QString &type);
    void clearTypeFilter();
    void setSubgenreFilter(Subgenre subgenre);
    void clearSubgenreFilter(); 
    void setWatchedFilter(bool watched);
    void setStarredFilter(bool starred);
    void clearFilters();
    bool hasActiveFilters() const;
    // Set the role to use for sorting
    void setSortRole(ContentModel::SortRole role);
    
    // Getters for current filters
    QString getTypeFilter() const { return m_typeFilter; }
    QList<Subgenre> getSubgenreFilters() const { return m_subgenreFilters; }
    bool getWatchedFilter() const { return m_filterWatched; }
    bool getStarredFilter() const { return m_filterStarred; }
    
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
    
private:
    QString m_titleFilter;
    QString m_typeFilter;
    QList<Subgenre> m_subgenreFilters;
    bool m_filterWatched = false;
    bool m_filterStarred = false;
    ContentModel::SortRole m_sortRole=ContentModel::SortRole::Title;
};

#endif // CONTENTPROXYMODEL_H
