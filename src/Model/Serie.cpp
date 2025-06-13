#include "./lib/Serie.h"

Serie::Serie():Video(), seasons(), episodes(), creator(), finished(){};

Serie::Serie(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
            const string& _platforms, const unsigned int& _duration, const unsigned int& _seasons, const unsigned int& _episodes, const string& _creator, const bool& _finished,
            unsigned int _inspiration, unsigned int  _prequel, unsigned int _sequel):
            Video(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms, _duration, _inspiration, _prequel, _sequel),
            seasons(_seasons),
            episodes(_episodes),
            creator(_creator),
            finished(_finished){}

string Serie::getType() const{
    return "Serie";
}

unsigned int Serie::getSeasons()const{
    return seasons;
}
unsigned int Serie::getEpisodes()const{
    return episodes;
}
string Serie::getCreator()const{
    return creator;
}
bool Serie::getFinished()const{
    return finished;
}

void Serie::setSeasons(const unsigned int& nseasons){
    seasons = nseasons;
}
void Serie::setEpisodes(const unsigned int& nepisodes){
    episodes = nepisodes;
}
void Serie::setCreator(string_view ncreator){
    creator = ncreator;
}
void Serie::setFinished(const bool& nfinished){
    finished = nfinished;
}

AttributeDisplayWindow* Serie::accept(Visitor* visitor){
    return visitor->visit(this);
}

CommonEditWindow* Serie::acceptEdit(Visitor* visitor){
    return visitor->visitEdit(this);
};

void Serie::toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ){
    xvisitor->toXml(this, doc, root);
}
void Serie::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};
