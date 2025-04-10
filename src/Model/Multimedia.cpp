#include "./lib/Multimedia.h"

Multimedia::Multimedia():Content(), producer(), platforms(){};

Multimedia::Multimedia(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
    const string& _platforms, unsigned int _inspiration):
            Content(_title, _subGenre, _description, _starred, _watched, _year, _image, _inspiration),
            producer(_producer),
            platforms(_platforms){};

string Multimedia::getProducer()const {
    return producer;
}

string Multimedia::getPlatforms()const{
    return platforms;
}

void Multimedia::setProducer(const string& _producer){
    producer = _producer;
}
void Multimedia::setPlatforms(const string& _platforms){
    platforms = _platforms;
}