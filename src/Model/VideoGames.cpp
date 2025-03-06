#include "./lib/VideoGames.h"

VideoGames::VideoGames(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
    string _language, string _gameEngine, unsigned int _expectedHours, QList <string> _platforms, Content* _inspiration=NULL):
    Multimedia(_title, _subGenre[], _description, _starred, _watched, _year, _image, _producer, 
        _language, _platforms, _inspiration),
    gameEngine(_gameEngine),
    expectedHours(_expectedHours)
    {}

string VideoGames::getGameEngine(){
    return gameEngine;
}

unsigned int VideoGames::getExpectedHours(){
    return expectedHours;
}

void VideoGames::setGameEngine(string _gameEngine){
    gameEngine = _gameEngine;
}

void VideoGames::setExpectedHours(unsigned int _expectedHours){
    expectedHours = _expectedHours;
}