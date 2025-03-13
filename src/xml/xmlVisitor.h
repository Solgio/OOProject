#ifndef XVISITOR_H
#define XVISITOR_H
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"

class xmlVisitor{
    public:
        virtual void toXml(Book *book) = 0;
        virtual void toXml(Comic *comic) = 0;
        virtual void toXml(Film *movie) = 0;
        virtual void toXml(Serie *serie) = 0;
        virtual void toXml(VideoGame *videogame) = 0;
};

#endif