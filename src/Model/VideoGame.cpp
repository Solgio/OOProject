#include "./lib/VideoGame.h"

VideoGame::VideoGame(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
    string _platforms, string _gameEngine, unsigned int _expectedHours, unsigned int _inspiration, gameType _gameType):
    Multimedia(_title, _subGenre, _description, _starred, _watched, _year, _image, _producer, _platforms, _inspiration),
    gameEngine(_gameEngine),
    expectedHours(_expectedHours),
    gameGenre(_gameType)
    {}

string VideoGame::getType() const{
    return "VideoGame";
}
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
void VideoGame::toXml(xmlVisitor* xvisitor){
    xvisitor->toXml(this);
};
void VideoGame::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};