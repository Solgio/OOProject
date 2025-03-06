#ifndef GAMES_H
#define GAMES_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Multimedia.h"

class VideoGames : public Multimedia {
   private:
        string gameEngine;
        // *TODO: se è possibile cambiarlo come Content?
        // ? enum gameType {FPS, RPG, RTS, MOBA, MMORPG, SIMULATION, SPORTS, PUZZLE, PLATFORMER, RACING, FIGHTING, SURVIVAL, ADVENTURE, ACTION, STRATEGY, 
        // ?  SANDBOX, TOWERDEFENSE, CARDGAME, BOARDGAME, PARTYGAME, EDUCATIONAL, MUSIC, CASUAL, ARCADE, SIMULATOR, VIRTUALREALITY, OTHER};
        unsigned int expectedHours;
    
    public:
        VideoGames(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _language, string _gameEngine, unsigned int _expectedHours, QList <string> _platforms, Content* _inspiration=NULL);
        
        string getGameEngine();
        
        // *TODO: da finire quando si conferma gameType
        // ? string getGameType();

        unsigned int getExpectedHours();
        
        void setGameEngine(string gameEngine);

        // *TODO: da finire quando si conferma gameType
        // ? void setGameType(string gameType);

        void setExpectedHours(unsigned int expectedHours);
        virtual ~Games(){
            // *TODO: connect(this, this.broadCastDelete(), tutti??, checkDeleteDependency())
        };

        
        //*TODO: private slot: 
        //? checkDeleteDependency(){ if( (*inspiration).isEqual(oggettoRicevuto) delete inspiration;){}  };
        // Un idea a grande linee
        
};

#endif