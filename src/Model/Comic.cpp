#include "./lib/Comic.h"

Comic::Comic(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _author, 
    string _publisher, unsigned int _pages, unsigned int _volume, string _illustrator, string _series, bool _finished, string _mainCharacter, Content* _inspiration=NULL):
    Book(_title, _subGenre, _description, _starred, _watched, _year, _image, _author, _publisher, _pages, _volume, _mainCharacter, _inspiration),
    illustrator(_illustrator), series(_series), finished(_finished){};


string Comic::getIllustrator() const{
    return illustrator;
};
string Comic::getSeries() const{
    return series;
};
bool Comic::getFinished() const{
    return finished;
};

void Comic::setIllustrator(const string& nillustrator){
    illustrator=nillustrator;
};
void Comic::setSeries(const string& nseries){
    series=nseries;
};
void Comic::setFinished(const bool& nfinished){
    (!finished)? finished=true : finished=false;
};

void Comic::accept(Visitor* visitor){
    visitor->visit(this);
};