#include "Visitor.h"
#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"

#include "DisplayWindows/AttributeDisplayWindow.h"
#include "DisplayWindows/BookDisplayWindow.h"
#include "DisplayWindows/ComicDisplayWindow.h"
#include "DisplayWindows/FilmDisplayWindow.h"
#include "DisplayWindows/SerieDisplayWindow.h"
#include "DisplayWindows/VideogameDisplayWindow.h"

#include "EditWindows/CommonEditWindow.h"
#include "EditWindows/BookEditWindow.h"
#include "EditWindows/ComicEditWindow.h"
#include "EditWindows/FilmEditWindow.h"
#include "EditWindows/SerieEditWindow.h"
#include "EditWindows/VideoGameEditWindow.h"

Visitor::Visitor(){}

AttributeDisplayWindow* Visitor::visit(Book *book){
    printf("Book visited\n");
    //display = new BookDisplayWindow(book);
    return new BookDisplayWindow(book);
};

AttributeDisplayWindow* Visitor::visit(Comic *comic){
    printf("Comic visited\n");
    display = new ComicDisplayWindow(comic);
    return display;
};

AttributeDisplayWindow* Visitor::visit(Film *movie){
    printf("Film visited\n");
    display = new FilmDisplayWindow(movie);
    return display;
};

AttributeDisplayWindow* Visitor::visit(Serie *serie){
    printf("Serie visited\n");
    display = new SerieDisplayWindow(serie);
    return display;
};

AttributeDisplayWindow* Visitor::visit(VideoGame *videogame){
    printf("VideoGame visited\n");
    display = new VideogameDisplayWindow(videogame);
    return display;
};

///Per le editWindow
CommonEditWindow* Visitor::visitEdit(Book *book){
    printf("Book visited\n");
    return new BookEditWindow(book);
};

CommonEditWindow* Visitor::visitEdit(Comic *comic){
    printf("Comic visited\n");
    return new ComicEditWindow(comic);
};

CommonEditWindow* Visitor::visitEdit(Film *movie){
    printf("Film visited\n");
    return new FilmEditWindow(movie);
};

CommonEditWindow* Visitor::visitEdit(Serie *serie){
    printf("Serie visited\n");
    return new SerieEditWindow(serie);
};

CommonEditWindow* Visitor::visitEdit(VideoGame *videogame){
    printf("VideoGame Edited\n");
    return new VideoGameEditWindow(videogame);
};

