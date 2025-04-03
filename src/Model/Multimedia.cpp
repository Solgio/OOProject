#include "./lib/Multimedia.h"
#include <iostream>
using std::cout;
using std::endl;


Multimedia::Multimedia(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
    string _platforms, unsigned int _inspiration):
            Content(_title, _subGenre, _description, _starred, _watched, _year, _image, _inspiration),
            producer(_producer),
            platforms(_platforms){};

string Multimedia::getProducer(){
    return producer;
}

string Multimedia::getPlatforms(){
    return platforms;
}

void Multimedia::setProducer(const string& _producer){
    producer = _producer;
}
void Multimedia::setPlatforms(const string& _platforms){
    platforms = _platforms;
}
void Multimedia::printContent() const{
    Content::printContent();
    cout << "Producer: " << producer << endl;
    cout << "Platforms: " << platforms << endl;
}