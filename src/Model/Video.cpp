#include "lib/Video.h"
#include "./lib/ScienceFictionLibrary.h" // Ensure the header file for ScienceFiction_Library is included

Video::Video():Multimedia(), duration(), prequel(0), sequel(0){};

Video:: Video(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
    const string& _platforms, const unsigned int& _duration, unsigned int _inspiration, unsigned int  _prequel, unsigned int _sequel):
    Multimedia(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms, _inspiration),
    duration(_duration),
    prequel(_prequel),
    sequel(_sequel){};


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
    prequel = _prequelId;
}

void Video::setSequel(const unsigned int& _sequelId){
    sequel = _sequelId;
}

bool Video::controllPrequel(){
    if(prequel != 0){
        // Check if the prequel ID exists in the library and if it is a Video type Content
        auto tprequel = dynamic_cast<Video*>(ScienceFiction_Library::getInstance().searchId(prequel));
        if(tprequel){
            if(tprequel->getSequel() != this->getId()){
                tprequel->setSequel(this->getId());
                return true;
            }
        }else{
            qDebug() << "Prequel with this Id not found";
            return false;
        }
    }
    return true;
}

bool Video::controllSequel(){
    if(sequel != 0){
    //Check if the sequel ID exists in the library and if it is a Video type Content
        auto tsequel=dynamic_cast<Video*>(ScienceFiction_Library::getInstance().searchId(sequel));
        if(tsequel){
            if(tsequel->getPrequel() != this->getId()){
                tsequel->setPrequel(this->getId());
                return true;
            }
        }else{
            qDebug() << "Sequel with this Id not found";
            return false;
        }
    }
    return true;
}
