#ifndef VISITOR_JSON_CPP
#define VISITOR_JSON_CPP

#include "VisitorJSon.h"
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Series.h"
#include "../Model/lib/VideoGame.h"

void VisitorJSon::saveToFile(Book *book){
    
};
void VisitorJSon::saveToFile(Comic *comic) = 0;
void VisitorJSon::saveToFile(Film *movie) = 0;
void VisitorJSon::saveToFile(Series *series) = 0;
void VisitorJSon::saveToFile(VideoGame *videogame) = 0;

#endif