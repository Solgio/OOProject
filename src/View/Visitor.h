#ifndef VISITOR_H
#define VISITOR_H

class Book;
class Comic;
class Film;
class Series;
class VideoGame;

class Visitor{
    public:
        virtual void visit(Book *book) = 0;
        virtual void visit(Comic *comic) = 0;
        virtual void visit(Film *movie) = 0;
        virtual void visit(Serie *serie) = 0;
        virtual void visit(VideoGame *videogame) = 0;
};
#endif