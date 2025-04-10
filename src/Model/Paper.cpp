#include "./lib/Paper.h"

Paper::Paper():Content(), author(), publisher(), pages(), volume(){};

Paper::Paper(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _author, 
    const string& _publisher, const unsigned int& _pages, const unsigned int& _volume, unsigned int _inspiration):
    Content(_title, _subGenre, _description, _starred, _watched, _year, _image, _inspiration), author(_author), publisher(_publisher), pages(_pages), volume(_volume){};

string Paper::getAuthor() const{
    return author;
};
string Paper::getPublisher() const{
    return publisher;
};
unsigned int Paper::getPages() const{
    return pages;
};
unsigned int Paper::getVolume() const{
    return volume;
};

void Paper::setAuthor(string_view nauthor){
    author=nauthor;
};
void Paper::setPublisher(string_view npublisher){
    publisher=npublisher;
};
void Paper::setPages(const unsigned int& npages){
    pages=npages;
};
void Paper::setVolume(const unsigned int& nvolume){
    volume=nvolume;
};