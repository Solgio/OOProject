#ifndef VISITOR_H
#define VISITOR_H
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"

class Visitor{
    public:
        virtual void visit(Book *book) = 0;
        virtual void visit(Comic *comic) = 0;
        virtual void visit(Film *movie) = 0;
        virtual void visit(Serie *serie) = 0;
        virtual void visit(VideoGame *videogame) = 0;
};
#endif