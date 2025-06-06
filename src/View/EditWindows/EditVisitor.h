#ifndef EDITVISITOR_H
#define EDITVISITOR_H

class Book;
class Comic;
class Serie;
class Film;
class VideoGame;
class CommonEditWindow;

class EditVisitor{

private:
    CommonEditWindow *childWindow;
public:
    EditVisitor();
    virtual CommonEditWindow* visit(Book *book);
    virtual CommonEditWindow* visit(Comic *comic);
    virtual CommonEditWindow* visit(Film *movie);
    virtual CommonEditWindow* visit(Serie *serie);
    virtual CommonEditWindow* visit(VideoGame *videogame);
};

#endif // EDITVISITOR_H
