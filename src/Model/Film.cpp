#include "./lib/Film.h"

Film::Film():Video(), director(), photoDirector(){};

Film::Film(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _director, 
    const string& _producer, const string& _platforms, const string& _photoDirector, const unsigned int& _duration, unsigned int _inspiration, unsigned int _prequel,
    unsigned int _sequel):
    Video(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms,  _duration, _inspiration, _prequel, _sequel), 
    director(_director), photoDirector(_photoDirector){};

string Film::getDirector() const{
    return director;
};
string Film::getPhotoDirector()  const{
    return photoDirector;
};

void Film::setDirector(string_view ndirector){
    director=ndirector;
};
void Film::setPhotoDirector(string_view nPhotoDirector){
    photoDirector=nPhotoDirector;
};  

void Film::accept(Visitor* visitor){
    visitor->visit(this);
};
void Film::toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ){
    xvisitor->toXml(this, doc, root);
};
void Film::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};