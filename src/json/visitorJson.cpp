#include "visitorJson.h"

#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"

void VisitorJson::toFileJson(Book *book){

    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", book->getTitle());

    
    oggettoJSon.insert("Genres", book->getSubgenre());  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", book->getDescription());
    oggettoJSon.insert("Year of Release", book->getYear());
    oggettoJSon.insert("Image", book->getImage()); // contiene la image path
    oggettoJSon.insert("Inspiration", inspiration->getTitle()); // Contiene il titolo dell'inspirazione

    //specifiche del "Book"
    oggettoJSon.insert("Main Character", book->getMainCharacter());
    //fine

    doc.setObject(oggettoJSon.toJson());
    libreria.write(doc);
    libreria.close();
};


void VisitorJson::toFileJson(Comic *comic){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", comic->getTitle());
    oggettoJSon.insert("Genres", comic->getSubgenre());  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", comic->getDescription());
    oggettoJSon.insert("Year of Release", comic->getYear());
    oggettoJSon.insert("Image", comic->getImage()); // contiene la image path
    oggettoJSon.insert("Inspiration", inspiration->getTitle()); // Contiene il titolo dell'inspirazione

    //specifiche del "Comic"
    oggettoJSon.insert("Illustrator", comic->getIllustrator());
    oggettoJSon.insert("Series", comic->getSerie());
    oggettoJSon.insert("Finished", comic->getFinished());
    //fine

    doc.setObject(oggettoJSon.toJson());
    libreria.write(doc);
    libreria.close();
};


void VisitorJson::toFileJson(Film *movie){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", movie->getTitle());
    oggettoJSon.insert("Genres", movie->getSubgenre());  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", movie->getDescription());
    oggettoJSon.insert("Year of Release", movie->getYear());
    oggettoJSon.insert("Image", movie->getImage()); // contiene la image path
    oggettoJSon.insert("Inspiration", inspiration->getTitle()); // Contiene il titolo dell'inspirazione

    //specifiche del "Film"
    oggettoJSon.insert("Director", movie->getDirector());
    oggettoJSon.insert("Photo Director", movie->getPhotoDirector());
    //fine

    doc.setObject(oggettoJSon.toJson());
    libreria.write(doc);
    libreria.close();
};


void VisitorJson::toFileJson(Serie *serie){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", serie->getTitle());
    oggettoJSon.insert("Genres", serie->getSubgenre());  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", serie->getDescription());
    oggettoJSon.insert("Year of Release", serie->getYear());
    oggettoJSon.insert("Image", serie->getImage()); // contiene la image path
    oggettoJSon.insert("Inspiration", inspiration->getTitle()); // Contiene il titolo dell'inspirazione

    //specifiche del "Film"
    oggettoJSon.insert("Seasons", serie->getSeasons());
    oggettoJSon.insert("Episodes", serie->getEpisodes());
    oggettoJSon.insert("Creator", serie->getCreator());
    oggettoJSon.insert("Finished", serie->getFinished());
    oggettoJSon.insert("Year End", serie->getYearOfEnd());
    //fine

    doc.setObject(oggettoJSon.toJson());
    libreria.write(doc);
    libreria.close();
};


void VisitorJson::toFileJson(VideoGame *videogame){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", videogame->getTitle());
    oggettoJSon.insert("Genres", videogame->getSubgenre());  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", videogame->getDescription());
    oggettoJSon.insert("Year of Release", videogame->getYear());
    oggettoJSon.insert("Image", videogame->getImage()); // contiene la image path
    oggettoJSon.insert("Inspiration", inspiration->getTitle()); // Contiene il titolo dell'inspirazione

    //specifiche del "Film"
    oggettoJSon.insert("Game Engine", videogame->getGameEngine());
    oggettoJSon.insert("Expected Hours Of Play", videogame->getExpectedHours());
    //fine

    doc.setObject(oggettoJSon.toJson());
    libreria.write(doc);
    libreria.close();
};  