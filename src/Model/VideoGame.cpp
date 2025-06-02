#include "./lib/VideoGame.h"

VideoGame::VideoGame():Multimedia(), gameEngine(), expectedHours(), gameGenre(){};

VideoGame::VideoGame(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
    const string& _platforms, const string& _gameEngine, const unsigned int& _expectedHours, const gameType& _gameType, unsigned int _inspiration):
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
    if(gameGenre == VideoGame::gameType::FPS){ return "FPS";}
    if(gameGenre == VideoGame::gameType::RPG ){ return "RPG";}
    if(gameGenre == VideoGame::gameType::ARPG ){ return "ARPG";}
    if(gameGenre == VideoGame::gameType::RTS){ return "RTS";}
    if(gameGenre == VideoGame::gameType::MOBA){ return "MOBA";}
    if(gameGenre == VideoGame::gameType::MMORPG){ return "MMORPG";}
    if(gameGenre == VideoGame::gameType::SIMULATION){ return "SIMULATION";}
    if(gameGenre == VideoGame::gameType::SPORTS){ return "SPORTS";}
    if(gameGenre == VideoGame::gameType::PUZZLE){ return "PUZZLE";}
    if(gameGenre == VideoGame::gameType::PLATFORMER){ return "PLATFORMER";}
    if(gameGenre == VideoGame::gameType::RACING){ return "RACING";}
    if(gameGenre == VideoGame::gameType::FIGHTING){ return "FIGHTING";}
    if(gameGenre == VideoGame::gameType::SURVIVAL){ return "SURVIVAL";}
    if(gameGenre == VideoGame::gameType::ADVENTURE){ return "ADVENTURE";}
    if(gameGenre == VideoGame::gameType::ACTION){ return "ACTION";}
    if(gameGenre == VideoGame::gameType::STRATEGY){ return "STRATEGY";}
    if(gameGenre == VideoGame::gameType::SANDBOX){ return "SANDBOX";}
    if(gameGenre == VideoGame::gameType::TOWERDEFENSE){ return "TOWERDEFENSE";}
    if(gameGenre == VideoGame::gameType::CARDGAME){ return "CARDGAME";}
    if(gameGenre == VideoGame::gameType::PARTYGAME){ return "PARTYGAME";}
    if(gameGenre == VideoGame::gameType::CASUAL){ return "CASUAL";}
    if(gameGenre == VideoGame::gameType::ARCADE){ return "ARCADE";}
    if(gameGenre == VideoGame::gameType::VIRTUALREALITY){ return "VIRTUALREALITY";}
    return nullptr;
}

enum VideoGame::gameType VideoGame::getGameTypeEnum() const{
    return gameGenre;
}

enum VideoGame::gameType VideoGame::stringToGametype(string_view tipo)const{
    if(tipo == "FPS"){ return VideoGame::gameType::FPS;}
    if(tipo == "RPG"){ return VideoGame::gameType::RPG;}
    if(tipo == "ARPG"){ return VideoGame::gameType::ARPG;}
    if(tipo == "RTS"){ return VideoGame::gameType::RTS;}
    if(tipo == "MOBA"){ return VideoGame::gameType::MOBA;}
    if(tipo == "MMORPG"){ return VideoGame::gameType::MMORPG;}
    if(tipo == "SIMULATION"){ return VideoGame::gameType::SIMULATION;}
    if(tipo == "SPORTS"){ return VideoGame::gameType::SPORTS;}
    if(tipo == "PUZZLE"){ return VideoGame::gameType::PUZZLE;}
    if(tipo == "PLATFORMER"){ return VideoGame::gameType::PLATFORMER;}
    if(tipo == "RACING"){ return VideoGame::gameType::RACING;}
    if(tipo == "FIGHTING"){ return VideoGame::gameType::FIGHTING;}
    if(tipo == "SURVIVAL"){ return VideoGame::gameType::SURVIVAL;}
    if(tipo == "ADVENTURE"){ return VideoGame::gameType::ADVENTURE;}
    if(tipo == "ACTION"){ return VideoGame::gameType::ACTION;}
    if(tipo == "STRATEGY"){ return VideoGame::gameType::STRATEGY;}
    if(tipo == "SANDBOX"){ return VideoGame::gameType::SANDBOX;}
    if(tipo == "TOWERDEFENSE"){ return VideoGame::gameType::TOWERDEFENSE;}
    if(tipo == "CARDGAME"){ return VideoGame::gameType::CARDGAME;}
    if(tipo == "PARTYGAME"){ return VideoGame::gameType::PARTYGAME;}
    if(tipo == "CASUAL"){ return VideoGame::gameType::CASUAL;}
    if(tipo == "ARCADE"){ return VideoGame::gameType::ARCADE;}
    if(tipo == "VIRTUALREALITY"){ return VideoGame::gameType::VIRTUALREALITY;}
    //TODO throw ERROR_ENUM;
    return VideoGame::gameType::FPS;
}

void VideoGame::setGameEngine(string_view _gameEngine){
    gameEngine = _gameEngine;
}
void VideoGame::setExpectedHours(const unsigned int& _expectedHours){
    expectedHours = _expectedHours;
}

void VideoGame::setGameType(gameType tipo){
    gameGenre = tipo;
}

AttributeDisplayWindow* VideoGame::accept(Visitor* visitor){
    return visitor->visit(this);
}
void VideoGame::toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ){
    xvisitor->toXml(this, doc, root);
};
void VideoGame::toJson(VisitorJson* visitorJson){
    visitorJson->toFileJson(this);
};
