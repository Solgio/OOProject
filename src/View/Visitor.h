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
        virtual QWidget* visit(Book *book) = 0;
        virtual QWidget* visit(Comic *comic) = 0;
        virtual QWidget* visit(Film *movie) = 0;
        virtual QWidget* visit(Serie *serie) = 0;
        virtual QWidget* visit(VideoGame *videogame) = 0;
};
#endif
