#include "Visitor.h"
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"

#include "DisplayWindows/BookDisplayWindow.h"
#include "DisplayWindows/ComicDisplayWindow.h"
#include "DisplayWindows/FilmDisplayWindow.h"
#include "DisplayWindows/SerieDisplayWindow.h"
#include "DisplayWindows/VideogameDisplayWindow.h"

QWidget* Visitor::visit(Book *book){
    printf("Book visited\n");
    display = new BookDisplayWindow(book);
    return display;
};

QWidget* Visitor::visit(Comic *comic){
    printf("Comic visited\n");
    display = new ComicDisplayWindow(comic);
    return display;
};

QWidget* Visitor::visit(Film *movie){
    printf("Film visited\n");
    display = new FilmDisplayWindow(movie);
    return display;
};

QWidget* Visitor::visit(Serie *serie){
    printf("Serie visited\n");
    display = new SerieDisplayWindow(serie);
    return display;
};

QWidget* Visitor::visit(VideoGame *videogame){
    printf("VideoGame visited\n");
    display = new VideogameDisplayWindow(videogame);
    return display;
};  
