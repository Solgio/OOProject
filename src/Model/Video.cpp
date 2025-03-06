#include "./lib/Video.h"

Video::Video(string _title, bool _subGenre[], string _description, bool _starred, bool _watched, unsigned int _year, string _producer, 
            string _language, QList <string> _platforms, string _country, Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL, unsigned int _quality[2]):
            Multimedia(_title, _subGenre, _description, _starred, _watched, _year, _producer, 
            _language, _platforms, _inspiration),
            prequel(_prequel),
            sequel(_sequel)
            {
                quality[0] = _quality[0];
                quality[1] = _quality[1];
            }


string Video::getQuality(){
    return (std::to_string(quality[0]), "x", std::to_string(quality[1]));
}

string Video::getCountry(){
    return country;
}

Video* Video::getPrequel(){
    return prequel;
}

Video* Video::getSequel(){
    return sequel;
}

void Video::setQuality(unsigned int _quality[2]){
    quality[0] = _quality[0];
    quality[1] = _quality[1];
}

void Video::setCountry(string _country){
    country = _country;
}

void Video::setPrequel(Video* _prequel){
    if(_prequel && _prequel != this){
        prequel = _prequel;
        _prequel->setSequel(this);
    }
    
}

void Video::setSequel(Video* _sequel){
    if(_sequel && _sequel != this){
        sequel = _sequel;
        _sequel->setPrequel(this);
    }
}

