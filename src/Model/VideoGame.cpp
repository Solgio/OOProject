#include "./lib/VideoGame.h"

VideoGame::VideoGame():Multimedia(), gameEngine(), expectedHours(), gameGenre(){};

VideoGame::VideoGame(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
    const string& _platforms, const string& _gameEngine, const unsigned int& _expectedHours, const gameType& _gameType, unsigned int _inspiration):
    Multimedia(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms, _inspiration),
    gameEngine(_gameEngine),
    expectedHours(_expectedHours),
    gameGenre(_gameType)
    {}

string VideoGame::getGameEngine() const{
    return gameEngine;
}
unsigned int VideoGame::getExpectedHours() const{
    return expectedHours;
}

string VideoGame::getGameType() const{
    return std::to_string(gameGenre);
}

void VideoGame::setGameEngine(string _gameEngine){
    gameEngine = _gameEngine;
}
void VideoGame::setExpectedHours(unsigned int _expectedHours){
    expectedHours = _expectedHours;
}

void VideoGame::setGameType(gameType tipo){
    gameGenre = tipo;
}

void VideoGame::accept(Visitor* visitor){
    visitor->visit(this);
}
void VideoGame::toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ){
    xvisitor->toXml(this, doc, root);
};
void VideoGame::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};