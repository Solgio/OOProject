#include "./lib/Serie.h"

Serie::Serie(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _platforms, unsigned int _duration, unsigned int _seasons, unsigned int _episodes, string _creator, bool _finished,
            Content* _inspiration, Video* _prequel, Video* _sequel):
            Video(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms, _duration, _inspiration, _prequel, _sequel),
            seasons(_seasons),
            episodes(_episodes),
            creator(_creator),
            finished(_finished){}

unsigned int Serie::getSeasons(){
    return seasons;
}
unsigned int Serie::getEpisodes(){
    return episodes;
}
string Serie::getCreator(){
    return creator;
}
bool Serie::getFinished(){
    return finished;
}



void Serie::setSeasons(unsigned int _seasons){
    seasons = _seasons;
}
void Serie::setEpisodes(unsigned int _episodes){
    episodes = _episodes;
}
void Serie::setCreator(string _creator){
    creator = _creator;
}
void Serie::setFinished(bool _finished){
    finished = _finished;
}

void Serie::accept(Visitor* visitor){
    visitor->visit(this);
}
void Serie::toXml(xmlVisitor* xvisitor){
    xvisitor->toXml(this);
}
void Serie::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};