#include "./lib/Multimedia.h"


Multimedia::Multimedia(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _language, QList <string> _platforms, Content* _inspiration=NULL):
            Content(_title, _subGenre, _description, _starred, _watched, _year, _image, _inspiration),
            producer(_producer),
            language(_language),
            platforms(_platforms) {
            };

string Multimedia::getProducer(){
    return producer;
}

string Multimedia::getLanguage(){
    return language;
}

QList <string> Multimedia::getPlatforms(){
    return platforms;
}

void Multimedia::setProducer(string _producer){
    producer = _producer;
}

void Multimedia::setLanguage(string _language){
    language = _language;
}

void Multimedia::setPlatforms(QList <string> _platmforms){
    platforms = _platmforms;
}


