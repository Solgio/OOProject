#ifndef XVISITOR_H
#define XVISITOR_H

class Content;
class Paper;
class Multimedia;
class Video;
class Book;
class Comic;
class Serie;
class Film;
class VideoGame;


class xmlVisitor{
    protected:
        void addElement(QDomDocument& doc, QDomElement& parent, const QString& name, const QString& value) const;
        void commonTags(Content *content, QDomDocument& doc, QDomElement& contentElem);
        void paperTags(Paper *content, QDomDocument& doc, QDomElement& paperElem);
        void multimediaTags(Multimedia *content, QDomDocument& doc, QDomElement& multimediaElem);
        void videoTags(Video *content, QDomDocument& doc, QDomElement& videoElem);

    public:
        virtual ~xmlVisitor() = default;
        virtual void toXml(Book *book, QDomDocument& doc, QDomElement& root);
        virtual void toXml(Comic *comic, QDomDocument& doc, QDomElement& root);
        virtual void toXml(Film *movie, QDomDocument& doc, QDomElement& root);
        virtual void toXml(Serie *serie, QDomDocument& doc, QDomElement& root);
        virtual void toXml(VideoGame *videogame, QDomDocument& doc, QDomElement& root);     
    };

#endif