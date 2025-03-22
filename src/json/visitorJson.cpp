#include "visitorJson.h"

#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"

void VisitorJson::setDirectory(QString path){
        dir.setPath(path);
    }
    void VisitorJson::setFileName(QString _fileName){
        fileName = _fileName;
    }

    void VisitorJson::setLibreria(QString path){
        if(libreria.open(QIODevice::ReadOnly)){
            libreria.close();
        }
        libreria.setFileName(path);
    }

    QDir VisitorJson::getDirectory(){
        return dir;
    }

    QString VisitorJson::getFileName(){
        return fileName;
    }




void VisitorJson::toFileJson(Book *book){

    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", QString::fromStdString(book->getTitle()));

    oggettoJSon.insert("Genres", QString::fromStdString(book->getSubgenre()));  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray

    oggettoJSon.insert("Description", QString::fromStdString(book->getDescription()));
    oggettoJSon.insert("Year of Release", int(book->getYear())); // Unsigned int da problemi di ambiguità
    oggettoJSon.insert("Image", QString::fromStdString(book->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(book->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione

    //specifiche del "Book"
    oggettoJSon.insert("Main Character", QString::fromStdString(book->getMainCharacter()));
    //fine

    doc.setObject(oggettoJSon);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(Comic *comic){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", QString::fromStdString(comic->getTitle()));
    oggettoJSon.insert("Genres", QString::fromStdString(comic->getSubgenre()));  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", QString::fromStdString(comic->getDescription()));
    oggettoJSon.insert("Year of Release", int(comic->getYear()));
    oggettoJSon.insert("Image", QString::fromStdString(comic->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(comic->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione

    //specifiche del "Comic"
    oggettoJSon.insert("Illustrator", QString::fromStdString(comic->getIllustrator()));
    oggettoJSon.insert("Series", QString::fromStdString(comic->getSerie()));
    oggettoJSon.insert("Finished", comic->getFinished());
    //fine

    doc.setObject(oggettoJSon);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(Film *movie){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", QString::fromStdString(movie->getTitle()));
    oggettoJSon.insert("Genres", QString::fromStdString(movie->getSubgenre()));  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", QString::fromStdString(movie->getDescription()));
    oggettoJSon.insert("Year of Release", int(movie->getYear()));
    oggettoJSon.insert("Image", QString::fromStdString(movie->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(movie->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione

    //specifiche del "Film"
    oggettoJSon.insert("Director", QString::fromStdString(movie->getDirector()));
    oggettoJSon.insert("Photo Director", QString::fromStdString(movie->getPhotoDirector()));
    //fine

    doc.setObject(oggettoJSon);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(Serie *serie){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", QString::fromStdString(serie->getTitle()));
    oggettoJSon.insert("Genres", QString::fromStdString(serie->getSubgenre()));  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", QString::fromStdString(serie->getDescription()));
    oggettoJSon.insert("Year of Release", int(serie->getYear()));
    oggettoJSon.insert("Image", QString::fromStdString(serie->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(serie->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione

    //specifiche del "Film"
    oggettoJSon.insert("Seasons", int(serie->getSeasons()));
    oggettoJSon.insert("Episodes", int(serie->getEpisodes()));
    oggettoJSon.insert("Creator", QString::fromStdString(serie->getCreator()));
    oggettoJSon.insert("Finished", serie->getFinished());
    oggettoJSon.insert("Year End", int(serie->getYearOfEnd()));
    //fine

    doc.setObject(oggettoJSon);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(VideoGame *videogame){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Title", QString::fromStdString(videogame->getTitle()));
    oggettoJSon.insert("Genres", QString::fromStdString(videogame->getSubgenre()));  //! non ho la minima idea se fuziona o no
                                                        //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", QString::fromStdString(videogame->getDescription()));
    oggettoJSon.insert("Year of Release", int(videogame->getYear()));
    oggettoJSon.insert("Image", QString::fromStdString(videogame->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(videogame->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione

    //specifiche del "Film"
    oggettoJSon.insert("Game Engine", QString::fromStdString(videogame->getGameEngine()));
    oggettoJSon.insert("Expected Hours Of Play", int(videogame->getExpectedHours()));
    //fine

    doc.setObject(oggettoJSon);
    libreria.write(doc.toJson());
    libreria.close();
};
