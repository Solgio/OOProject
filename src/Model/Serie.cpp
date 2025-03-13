#include "./lib/Serie.h"

Serie::Serie(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _language, QList <string> _platforms, string _country, unsigned int _seasons, unsigned int _episodes, string _creator, bool _finished, unsigned int _yearOfEnd, 
            Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL, unsigned int quality[2]):
            Video(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, 
                _language, _platforms, _country, _inspiration, _prequel, _sequel, quality),
            seasons(_seasons),
            episodes(_episodes),
            creator(_creator),
            finished(_finished),
            yearOfEnd(_yearOfEnd){}

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

unsigned int Serie::getYearOfEnd(){
    return yearOfEnd;
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

void Serie::setYearOfEnd(unsigned int _yearOfEnd){
    yearOfEnd = _yearOfEnd;
}

void Serie::accept(Visitor* visitor){
    visitor->visit(this);
}
void Serie::toXml(xmlVisitor* xvisitor){
    xvisitor->toXml(this);
}