// ContentModel.cpp
#include "ContentModel.h"
#include "../Model/lib/ScienceFictionLibrary.h"
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"
using std::underlying_type_t;

ContentModel::ContentModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    refreshData();
}

int ContentModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_contents.size();
}

int ContentModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 5; // Title, Type, Genre, Watched, Starred
}

QVariant ContentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_contents.size()))
        return QVariant();

    Content *content = m_contents[index.row()];

    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 0:
            return QString::fromStdString(content->getTitle());
        case 1:
            if (dynamic_cast<Book *>(content))
                return "Book";
            else if (dynamic_cast<Comic *>(content))
                return "Comic";
            else if (dynamic_cast<Film *>(content))
                return "Film";
            else if (dynamic_cast<Serie *>(content))
                return "Serie";
            else if (dynamic_cast<VideoGame *>(content))
                return "VideoGame";
            else
                return "Unknown";
        case 2:
            return QString::fromStdString(content->getSubgenreString());
        case 3:
            return content->getWatched() ? "Yes" : "No";
        case 4:
            return content->getStarred() ? "Yes" : "No";
        default:
            return QVariant();
        }
    case Qt::ToolTipRole:
        switch (index.column())
        {
        case 0:
            return QString::fromStdString(content->getTitle());
        case 2:
            return QString::fromStdString(content->getSubgenreString());
        default:
            return QVariant();
        }
    case static_cast<underlying_type_t<Roles>>(Roles::TitleRole):
        return QString::fromStdString(content->getTitle());
    case static_cast<underlying_type_t<Roles>>(Roles::TypeRole):
        if (dynamic_cast<Book *>(content))
            return "Book";
        else if (dynamic_cast<Comic *>(content))
            return "Comic";
        else if (dynamic_cast<Film *>(content))
            return "Film";
        else if (dynamic_cast<Serie *>(content))
            return "Serie";
        else if (dynamic_cast<VideoGame *>(content))
            return "VideoGame";
        else
            return "Unknown";
    case static_cast<underlying_type_t<Roles>>(Roles::SubgenreRole):
        return content->getSubgenre();
    case static_cast<underlying_type_t<Roles>>(Roles::WatchedRole):
        return content->getWatched();
    case static_cast<underlying_type_t<Roles>>(Roles::StarredRole):
        return content->getStarred();
    case static_cast<underlying_type_t<Roles>>(Roles::YearRole):
        return content->getYear();
    case static_cast<underlying_type_t<Roles>>(Roles::ContentPtrRole):
        return QVariant::fromValue(content);

    // New roles for preview cards
    case static_cast<underlying_type_t<Roles>>(Roles::CoverImageRole):
        return QString::fromStdString(content->getImage());
    case static_cast<underlying_type_t<Roles>>(Roles::CreatorRole):
    {
        // Get creator based on content type
        if (const auto *book = dynamic_cast<Book *>(content))
            return QString::fromStdString(book->getAuthor());
        else if (const auto *comic = dynamic_cast<Comic *>(content))
            return QString::fromStdString(comic->getAuthor());
        else if (const auto *film = dynamic_cast<Film *>(content))
            return QString::fromStdString(film->getDirector());
        else if (const auto *serie = dynamic_cast<Serie *>(content))
            return QString::fromStdString(serie->getCreator());
        else if (const auto *game = dynamic_cast<VideoGame *>(content))
            return QString::fromStdString(game->getGameEngine());
        else
            return "Unknown";
    }
    default:
        return QVariant();
    }
}

QVariant ContentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
    case 0:
        return "Title";
    case 1:
        return "Type";
    case 2:
        return "Genre";
    case 3:
        return "Watched";
    case 4:
        return "Starred";
    default:
        return QVariant();
    }
}

Qt::ItemFlags ContentModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void ContentModel::refreshData()
{
    beginResetModel();
    m_contents.clear();

    auto &library = ScienceFiction_Library::getInstance();
    for (const auto &content : library.getContentList())
    {
        m_contents.push_back(content.get());
    }

    endResetModel();
}

Content *ContentModel::getContent(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_contents.size()))
        return nullptr;
    return m_contents[index.row()];
}

Content *ContentModel::getContent(int row) const
{
    if (row < 0 || row >= static_cast<int>(m_contents.size()))
        return nullptr;
    return m_contents[row];
}

QHash<int, QByteArray> ContentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<underlying_type_t<Roles>>(Roles::TitleRole)] = "title";
    roles[static_cast<underlying_type_t<Roles>>(Roles::TypeRole)] = "type";
    roles[static_cast<underlying_type_t<Roles>>(Roles::SubgenreRole)] = "subgenre";
    roles[static_cast<underlying_type_t<Roles>>(Roles::WatchedRole)] = "watched";
    roles[static_cast<underlying_type_t<Roles>>(Roles::StarredRole)] = "starred";
    roles[static_cast<underlying_type_t<Roles>>(Roles::YearRole)] = "year";
    roles[static_cast<underlying_type_t<Roles>>(Roles::ContentPtrRole)] = "content";
    roles[static_cast<underlying_type_t<Roles>>(Roles::CoverImageRole)] = "coverImage";
    roles[static_cast<underlying_type_t<Roles>>(Roles::CreatorRole)] = "creator";
    return roles;
}

QVariant ContentModel::getSortValue(Content *content, SortRole role) const
{
    if (!content)
        return QVariant();

    switch (role)
    {
    case SortRole::Title:
        return QString::fromStdString(content->getTitle());

    case SortRole::Type:
        if (dynamic_cast<Book *>(content))
            return "Book";
        else if (dynamic_cast<Comic *>(content))
            return "Comic";
        else if (dynamic_cast<Film *>(content))
            return "Film";
        else if (dynamic_cast<Serie *>(content))
            return "Serie";
        else if (dynamic_cast<VideoGame *>(content))
            return "VideoGame";
        else
            return "Unknown";

        case SortRole::Year:
        return content->getYear();

    case SortRole::Creator:
    {
        // Get creator based on content type
        if (auto *book = dynamic_cast<Book *>(content))
            return QString::fromStdString(book->getAuthor());
        else if (auto *comic = dynamic_cast<Comic *>(content))
            return QString::fromStdString(comic->getAuthor());
        else if (auto *film = dynamic_cast<Film *>(content))
            return QString::fromStdString(film->getDirector());
        else if (auto *serie = dynamic_cast<Serie *>(content))
            return QString::fromStdString(serie->getCreator());
        else if (auto *game = dynamic_cast<VideoGame *>(content))
            return QString::fromStdString(game->getGameEngine());
        else
            return "Unknown";
    }

    default:
        return QVariant();
    }
}
