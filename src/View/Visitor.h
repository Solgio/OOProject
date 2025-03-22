#ifndef VISITOR_H
#define VISITOR_H

class Book;
class Comic;
<<<<<<< HEAD
class Film;
class Series;
=======
class Serie;
class Film;
>>>>>>> 036cb7cefac9b23858c3e367ccbf4260efa69d4a
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