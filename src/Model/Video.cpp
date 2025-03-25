#include "./lib/Video.h"

Video:: Video(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
    string _platforms, unsigned int _duration, Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL):
    Multimedia(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms, _inspiration),
    prequel(_prequel),
    sequel(_sequel),
    duration(_duration){};



unsigned int& Video::getDuration(){
    return duration;
}

Video* Video::getPrequel(){
    return prequel;
}

Video* Video::getSequel(){
    return sequel;
}

void Video::setDuration(unsigned int _duration){
    duration = _duration;
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