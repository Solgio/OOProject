#include "./lib/Comic.h"

Comic::Comic():Book(), illustrator(), serie(), finished(){};

Comic::Comic(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _author, 
    const string& _publisher, const unsigned int& _pages, const unsigned int& _volume, const string& _illustrator, const string& _serie, const bool& _finished, const string& _mainCharacter, unsigned int _inspiration):
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
    finished=nfinished;
    //(!finished)? finished=true : finished=false;
};

void Comic::accept(Visitor* visitor){
    visitor->visit(this);
};
void Comic::toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ){
    xvisitor->toXml(this, doc, root);
};
void Comic::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};