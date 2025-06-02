#ifndef VISITOR_H
#define VISITOR_H

#include <QWidget>
class Book;
class Comic;
class Serie;
class Film;
class VideoGame;
class AttributeDisplayWindow;

class Visitor: public QWidget{
    Q_OBJECT

    private:
        AttributeDisplayWindow *display;

    public:
        Visitor();
        virtual AttributeDisplayWindow* visit(Book *book);
        virtual AttributeDisplayWindow* visit(Comic *comic);
        virtual AttributeDisplayWindow* visit(Film *movie);
        virtual AttributeDisplayWindow* visit(Serie *serie);
        virtual AttributeDisplayWindow* visit(VideoGame *videogame);
};
#endif
