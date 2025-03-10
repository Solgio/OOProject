#include "./lib/Series.h"

Series::Series(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _language, QList <string> _platforms, string _country, unsigned int _seasons, unsigned int _episodes, string _creator, bool _finished, unsigned int _yearOfEnd, 
            Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL, unsigned int quality[2]):
            Video(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, 
                _language, _platforms, _country, _inspiration, _prequel, _sequel, quality),
            seasons(_seasons),
            episodes(_episodes),
            creator(_creator),
            finished(_finished),
            yearOfEnd(_yearOfEnd){}

unsigned int Series::getSeasons(){
    return seasons;
}

unsigned int Series::getEpisodes(){
    return episodes;
}
string Series::getCreator(){
    return creator;
}

bool Series::getFinished(){
    return finished;
}

unsigned int Series::getYearOfEnd(){
    return yearOfEnd;
}

void Series::setSeasons(unsigned int _seasons){
    seasons = _seasons;
}

void Series::setEpisodes(unsigned int _episodes){
    episodes = _episodes;
}

void Series::setCreator(string _creator){
    creator = _creator;
}

void Series::setFinished(bool _finished){
    finished = _finished;
}

void Series::setYearOfEnd(unsigned int _yearOfEnd){
    yearOfEnd = _yearOfEnd;
}

void Series::accept(Visitor* visitor){
    visitor->visit(this);
}