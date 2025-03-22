#ifndef XVISITOR_H
#define XVISITOR_H
#include <QFile> // per accedere/creare file
#include <QDir> // per gestire la directory
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Book;
class Comic;
class Serie;
class Film;
class VideoGame;


class xmlVisitor{
    public:
        virtual void toXml(Book *book) = 0;
        virtual void toXml(Comic *comic) = 0;
        virtual void toXml(Film *movie) = 0;
        virtual void toXml(Serie *serie) = 0;
        virtual void toXml(VideoGame *videogame) = 0;
};

#endif