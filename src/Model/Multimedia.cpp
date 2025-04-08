#include "./lib/Multimedia.h"

Multimedia::Multimedia():Content(), producer(), platforms(){};

Multimedia::Multimedia(string _title, unsigned int  _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
    string _platforms, unsigned int _inspiration):
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