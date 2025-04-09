#include "./lib/Book.h"

Book::Book():Paper(), mainCharacter(){};

Book::Book(string& _title, unsigned int  _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _author, 
    string _publisher, unsigned int _pages, unsigned int _volume, string _mainCharacter, unsigned int _inspiration):
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