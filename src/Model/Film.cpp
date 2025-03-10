#include "./lib/Film.h"

string Film::getDirector() const{
    return director;
};
string Film::getPhotoDirector()  const{
    return photoDirector;
};
string Film::getScriptwriter() const{
    return scriptwriter;
};
unsigned int Film::getDuration() const{
    return duration;
};

void Film::setDirector(const string& ndirector){
    director=ndirector;
};
void Film::setPhotoDirector(const string& nPhotoDirector){
    photoDirector=nPhotoDirector;
};
void Film::setScriptwriter(const string& nscriptwriter){
    scriptwriter=nscriptwriter;
};
void Film::setDuration(const unsigned int& nduration){
    duration=nduration;
};  

void Film::accept(Visitor* visitor){
    visitor->visit(this);
};