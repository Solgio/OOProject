#ifndef GAMES_H
#define GAMES_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Multimedia.h"

class VideoGame : public Multimedia {
   private:
        string gameEngine;
        unsigned int expectedHours;
        // *TODO: se è possibile cambiarlo come Content?
        // ? enum gameType {FPS, RPG, RTS, MOBA, MMORPG, SIMULATION, SPORTS, PUZZLE, PLATFORMER, RACING, FIGHTING, SURVIVAL, ADVENTURE, ACTION, STRATEGY, 
        // ?  SANDBOX, TOWERDEFENSE, CARDGAME, BOARDGAME, PARTYGAME, EDUCATIONAL, MUSIC, CASUAL, ARCADE, SIMULATOR, VIRTUALREALITY, OTHER};
    
    public:
        VideoGame(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
                  string _platforms, string _gameEngine, unsigned int _expectedHours, Content* _inspiration=nullptr);
        
        string getGameEngine();
        
        // *TODO: da finire quando si conferma gameType
        // ? string getGameType();

        unsigned int getExpectedHours();
        
        void setGameEngine(string gameEngine);

        // *TODO: da finire quando si conferma gameType
        // ? void setGameType(string gameType);

        void setExpectedHours(unsigned int expectedHours);
        virtual ~VideoGame(){
            // *TODO: connect(this, this.broadCastDelete(), tutti??, checkDeleteDependency())
        };

        
        //*TODO: private slot: 
        //? checkDeleteDependency(){ if( (*inspiration).isEqual(oggettoRicevuto) delete inspiration;){}  };
        // Un idea a grande 
        
        virtual void accept(Visitor* visitor) override;
        virtual void toXml(xmlVisitor* xvisitor);
        virtual void toJson(VisitorJson* vistitorJson);
        
};

#endif