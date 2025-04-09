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
        VideoGame(string& _title, unsigned int&  _subGenre, string& _description, bool& _starred, bool& _watched, unsigned int& _year, string& _image, string& _producer, 
                  string& _platforms, string& _gameEngine, unsigned int& _expectedHours, gameType& _gameType, unsigned int _inspiration=0);
        
      
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