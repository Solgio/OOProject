#ifndef VISITOR_JSON_H
#define VISITOR_JSON_H

#include "Visitor.h"

class VisitorJSON{
    public:
        virtual void saveToFile(Book *book) = 0;
        virtual void saveToFile(Comic *comic) = 0;
        virtual void saveToFile(Film *movie) = 0;
        virtual void saveToFile(Series *series) = 0;
        virtual void saveToFile(VideoGame *videogame) = 0;
};
#endif