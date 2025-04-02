#include "./lib/Paper.h"

Paper::Paper(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _author, 
    string _publisher, unsigned int _pages, unsigned int _volume, unsigned int _inspiration):
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

void Paper::setAuthor(const string& nauthor){
    author=nauthor;
};
void Paper::setPublisher(const string& npublisher){
    publisher=npublisher;
};
void Paper::setPages(const unsigned int& npages){
    pages=npages;
};
void Paper::setVolume(const unsigned int& nvolume){
    volume=nvolume;
};