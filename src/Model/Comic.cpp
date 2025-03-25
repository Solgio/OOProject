#include "./lib/Comic.h"

Comic::Comic(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _author, 
    string _publisher, unsigned int _pages, unsigned int _volume, string _illustrator, string _serie, bool _finished, string _mainCharacter, Content* _inspiration=NULL):
    Book(_title, _subGenre, _description, _starred, _watched, _year, _image, _author, _publisher, _pages, _volume, _mainCharacter, _inspiration),
    illustrator(_illustrator), serie(_serie), finished(_finished){};


string Comic::getIllustrator() const{
    return illustrator;
};
string Comic::getSerie() const{
    return serie;
};
bool Comic::getFinished() const{
    return finished;
};

void Comic::setIllustrator(const string& nillustrator){
    illustrator=nillustrator;
};
void Comic::setSerie(const string& nserie){
    serie=nserie;
};
void Comic::setFinished(const bool& nfinished){
    (!finished)? finished=true : finished=false;
};

void Comic::accept(Visitor* visitor){
    visitor->visit(this);
};
void Comic::toXml(xmlVisitor* xvisitor){
    xvisitor->toXml(this);
};
void Comic::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};