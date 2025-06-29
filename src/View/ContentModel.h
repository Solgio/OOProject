#ifndef CONTENTMODEL_H
#define CONTENTMODEL_H

#include <QAbstractTableModel>
#include "../Model/lib/Content.h"

class ContentModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum class Roles {
        TitleRole = Qt::UserRole + 1,
        TypeRole,
        SubgenreRole,
        WatchedRole,
        StarredRole,
        YearRole,
        ContentPtrRole,
        CoverImageRole,
        CreatorRole,

    };
    
    // Sorting roles enum
    enum class SortRole {
        Title,
        Type,
        Year,
        Creator
    };

    explicit ContentModel(QObject *parent = nullptr);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    
    void refreshData();
    Content* getContent(const QModelIndex &index) const;
    Content* getContent(int row) const;

    QHash<int, QByteArray> roleNames() const override;
    
    // Get a value for sorting based on the specified role
    QVariant getSortValue(Content* content, SortRole role) const;

private:
    std::vector<Content*> m_contents;
};

#endif // CONTENTMODEL_H
