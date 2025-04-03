#include "lib/Video.h"
#include "./lib/ScienceFictionLibrary.h" // Ensure the header file for ScienceFiction_Library is included

Video:: Video(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
    string _platforms, unsigned int _duration, unsigned int _inspiration, unsigned int  _prequel, unsigned int _sequel):
    Multimedia(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms, _inspiration),
    prequel(_prequel),
    sequel(_sequel),
    duration(_duration){};



unsigned int Video::getDuration()const{
    return duration;
}

unsigned int Video::getPrequel()const{
    return prequel;
}

unsigned int Video::getSequel()const{
    return sequel;
}

void Video::setDuration(const unsigned int& _duration){
    duration = _duration;
}

void Video::setPrequel(const unsigned int& _prequelId){
    Video* tprequel = dynamic_cast<Video*>(ScienceFiction_Library::getInstance().searchId(_prequelId));
    if(tprequel){
        prequel = _prequelId;
        tprequel->setSequel(this->getId());
    }
    else{
        qDebug() << "Prequel with this Id not found";
    }
}

void Video::setSequel(const unsigned int& _sequelId){
    Video* tsequel=dynamic_cast<Video*>(ScienceFiction_Library::getInstance().searchId(_sequelId));
    if(tsequel){
        sequel = _sequelId;
        tsequel->setPrequel(this->getId());
    }
    else{
        qDebug() << "Sequel with this Id not found";
    }
}