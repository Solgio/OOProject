#include "Visitor.h"
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Series.h"
#include "../Model/lib/VideoGame.h"

void Visitor::visit(Book *book){
    printf("Book visited\n");
    //! Da inserire la UI personalizzata specifica per ognuno (Ogni content type avrà una UI diversa)
};
void Visitor::visit(Comic *comic){
    printf("Comic visited\n");
};
void Visitor::visit(Film *movie){
    printf("Film visited\n");
};
void Visitor::visit(Series *series){
    printf("Series visited\n");
};
void Visitor::visit(VideoGame *videogame){
    printf("VideoGame visited\n");
};  