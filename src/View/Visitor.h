#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Series.h"
#include "../Model/lib/VideoGame.h"

class Visitor{
    public:
        virtual void visit(Book *book) = 0;
        virtual void visit(Comic *comic) = 0;
        virtual void visit(Film *movie) = 0;
        virtual void visit(Series *series) = 0;
        virtual void visit(VideoGame *videogame) = 0;
};