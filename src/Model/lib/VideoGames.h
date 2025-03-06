#ifndef GAMES_H
#define GAMES_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Video.h"

class Games : public Multimedia {
   private:
        string gameEngine;
        enum gameType {FPS, RPG, RTS, MOBA, MMORPG, SIMULATION, SPORTS, PUZZLE, PLATFORMER, RACING, FIGHTING, SURVIVAL, ADVENTURE, ACTION, STRATEGY, 
            SANDBOX, TOWERDEFENSE, CARDGAME, BOARDGAME, PARTYGAME, EDUCATIONAL, MUSIC, CASUAL, ARCADE, SIMULATOR, VIRTUALREALITY, OTHER};
        unsigned int expectedHours;
    
    public:
        Games(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _language, string _gameEngine, unsigned int _expectedHours, QList <string> _platforms, Content* _inspiration=NULL);
        
        string getGameEngine();
        string getGameType();
        unsigned int getExpectedHours();
        
        void setGameEngine(string gameEngine);
        void setGameType(string gameType);
        void setExpectedHours(unsigned int expectedHours);
        virtual ~Games();
};

#endif