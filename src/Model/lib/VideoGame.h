#ifndef GAMES_H
#define GAMES_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Multimedia.h"

class VideoGame : public Multimedia {
    public:
    enum gameType {FPS, RPG, RTS, MOBA, MMORPG, SIMULATION, SPORTS, PUZZLE, PLATFORMER, RACING, FIGHTING, SURVIVAL, ADVENTURE, ACTION, STRATEGY, 
        SANDBOX, TOWERDEFENSE, CARDGAME, PARTYGAME, CASUAL, ARCADE, VIRTUALREALITY};

        VideoGame();
        VideoGame(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
            const string& _platforms, const string& _gameEngine, const unsigned int& _expectedHours, const gameType& _gameType, unsigned int _inspiration=0);
        
      
        string getGameEngine() const;
        
        string getGameType() const;

        unsigned int getExpectedHours() const;
        
        void setGameEngine(string gameEngine);

        void setGameType(gameType tipo);

        void setExpectedHours(unsigned int expectedHours);
        virtual ~VideoGame();
        
        virtual void accept(Visitor* visitor) override;
        virtual void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root );
        virtual void toJson(VisitorJson* vistitorJson);

    private:
        string gameEngine;
        unsigned int expectedHours;
        gameType gameGenre;
        
};

#endif