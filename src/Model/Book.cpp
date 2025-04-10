#include "./lib/Book.h"

Book::Book():Paper(), mainCharacter(){};

Book::Book(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _author, 
    const string& _publisher, const unsigned int& _pages, const unsigned int& _volume, const string& _mainCharacter, unsigned int _inspiration):
    Paper(_title, _subGenre, _description, _starred, _watched, _year,_image, _author, _publisher, _pages, _volume, _inspiration), mainCharacter(_mainCharacter){};

string Book::getMainCharacter() const{
    return mainCharacter;
};  

void Book::setMainCharacter(const string& nmainCharacter){
    mainCharacter=nmainCharacter;
};

void Book::accept(Visitor* visitor){
    visitor->visit(this);
};

void Book::toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ){
    xvisitor->toXml(this, doc, root);
};

void Book::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};