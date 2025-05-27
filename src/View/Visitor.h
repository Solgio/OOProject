#ifndef VISITOR_H
#define VISITOR_H

#include <QWidget>
class Book;
class Comic;
class Serie;
class Film;
class VideoGame;

#include "DisplayWindows/AttributeDisplayWindow.h"

class Visitor: public QWidget{
    Q_OBJECT

    private:
        AttributeDisplayWindow *display;

    public:
        virtual QWidget* visit(Book *book);
        virtual QWidget* visit(Comic *comic);
        virtual QWidget* visit(Film *movie);
        virtual QWidget* visit(Serie *serie);
        virtual QWidget* visit(VideoGame *videogame);
};
#endif
