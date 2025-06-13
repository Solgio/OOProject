#ifndef VISITOR_H
#define VISITOR_H

#include <QWidget>
class Book;
class Comic;
class Serie;
class Film;
class VideoGame;
class AttributeDisplayWindow;
class CommonEditWindow;

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
        virtual CommonEditWindow* visitEdit(Book *book);
        virtual CommonEditWindow* visitEdit(Comic *comic);
        virtual CommonEditWindow* visitEdit(Film *movie);
        virtual CommonEditWindow* visitEdit(Serie *serie);
        virtual CommonEditWindow* visitEdit(VideoGame *videogame);
};
#endif
