#ifndef XVISITOR_H
#define XVISITOR_H

class Book;
class Comic;
class Serie;
class Film;
class VideoGame;


class xmlVisitor{
    public:
        virtual ~xmlVisitor() = default;
        virtual void toXml(Book *book, QDomDocument& doc, QDomElement& root);
        virtual void toXml(Comic *comic, QDomDocument& doc, QDomElement& root);
        virtual void toXml(Film *movie, QDomDocument& doc, QDomElement& root);
        virtual void toXml(Serie *serie, QDomDocument& doc, QDomElement& root);
        virtual void toXml(VideoGame *videogame, QDomDocument& doc, QDomElement& root);
};

#endif