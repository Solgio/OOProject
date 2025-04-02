#include "./lib/Film.h"


Film::Film(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _director, 
    string _producer, string _platforms, string _photoDirector, unsigned int _duration, unsigned int _inspiration, unsigned int _prequel,
    unsigned int _sequel):
    Video(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms,  _duration, _inspiration, _prequel, _sequel), 
    director(_director), photoDirector(_photoDirector){};

string Film::getType() const{
    return "Film";
};
string Film::getDirector() const{
    return director;
};
string Film::getPhotoDirector()  const{
    return photoDirector;
};

void Film::setDirector(const string& ndirector){
    director=ndirector;
};
void Film::setPhotoDirector(const string& nPhotoDirector){
    photoDirector=nPhotoDirector;
};  

void Film::accept(Visitor* visitor){
    visitor->visit(this);
};
void Film::toXml(xmlVisitor* xvisitor){
    xvisitor->toXml(this);
};
void Film::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};