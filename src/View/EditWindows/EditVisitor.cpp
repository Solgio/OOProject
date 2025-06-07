#include "EditVisitor.h"
#include "BookEditWindow.h"
#include "ComicEditWindow.h"
#include "FilmEditWindow.h"
#include "SerieEditWindow.h"
#include "VideoGameEditWindow.h"

EditVisitor::EditVisitor() {}

CommonEditWindow* EditVisitor::visit(Book *book){
    childWindow = new BookEditWindow(book);
    return childWindow;
};

CommonEditWindow* EditVisitor::visit(Comic *comic){
    childWindow = new ComicEditWindow(comic);
    return childWindow;
};

CommonEditWindow* EditVisitor::visit(Film *movie){
    childWindow = new FilmEditWindow(movie);
    return childWindow;
};

CommonEditWindow* EditVisitor::visit(Serie *serie){
    childWindow = new SerieEditWindow(serie);
    return childWindow;
};

CommonEditWindow* EditVisitor::visit(VideoGame *videogame){
    childWindow = new VideoGameEditWindow(videogame);
    return childWindow;
};
