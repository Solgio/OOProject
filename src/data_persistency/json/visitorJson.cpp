#include "visitorJson.h"

#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"

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




void VisitorJson::toFileJson(const Book *book){

    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonDocument doc;

    QJsonObject oggettoJSon;

    
    oggettoJSon.insert("Title", QString::fromStdString(book->getTitle()));
    oggettoJSon.insert("Genres", int(book->getSubgenre()));  
    oggettoJSon.insert("Description", QString::fromStdString(book->getDescription()));
    oggettoJSon.insert("Year of Release", int(book->getYear())); // Unsigned int da problemi di ambiguità
    oggettoJSon.insert("Image", QString::fromStdString(book->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(book->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione
    oggettoJSon.insert("Watched", book->getWatched());
    oggettoJSon.insert("Starred", book->getStarred());

    //Paper
    oggettoJSon.insert("Author", QString::fromStdString(book->getAuthor()));
    oggettoJSon.insert("Publisher", QString::fromStdString(book->getPublisher()));
    oggettoJSon.insert("Pages", int(book->getPages()));
    oggettoJSon.insert("Volume", int(book->getVolume()));

    /*
    insertPaper(book, oggettoJSon); //contiene anche insertContent(...);
    */

    //specifiche del "Book"
    oggettoJSon.insert("Main Character", QString::fromStdString(book->getMainCharacter()));
    //fine

    QJsonObject tipo;
    tipo.insert("Book", oggettoJSon);
    
    doc.setObject(tipo);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(Comic *comic){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Type", "Comic");
    oggettoJSon.insert("Title", QString::fromStdString(comic->getTitle()));
    oggettoJSon.insert("Genres", int(comic->getSubgenre())); 
    oggettoJSon.insert("Description", QString::fromStdString(comic->getDescription()));
    oggettoJSon.insert("Year of Release", int(comic->getYear()));
    oggettoJSon.insert("Image", QString::fromStdString(comic->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(comic->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione
    oggettoJSon.insert("Watched", comic->getWatched());
    oggettoJSon.insert("Starred", comic->getStarred());

    //Paper
    oggettoJSon.insert("Author", QString::fromStdString(comic->getAuthor()));
    oggettoJSon.insert("Publisher", QString::fromStdString(comic->getPublisher()));
    oggettoJSon.insert("Pages", int(comic->getPages()));
    oggettoJSon.insert("Volume", int(comic->getVolume()));

    

    //Book
    oggettoJSon.insert("Main Character", QString::fromStdString(comic->getMainCharacter()));

    //specifiche del "Comic"
    oggettoJSon.insert("Illustrator", QString::fromStdString(comic->getIllustrator()));
    oggettoJSon.insert("Series", QString::fromStdString(comic->getSerie()));
    oggettoJSon.insert("Finished", comic->getFinished());
    //fine

    QJsonObject tipo;
    tipo.insert("Comic", oggettoJSon);
    
    doc.setObject(tipo);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(Film *movie){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Type", "Film");
    oggettoJSon.insert("Title", QString::fromStdString(movie->getTitle()));
    oggettoJSon.insert("Genres", int(movie->getSubgenre()));                                                     //! Da fare probabilmente con JsonArray
    oggettoJSon.insert("Description", QString::fromStdString(movie->getDescription()));
    oggettoJSon.insert("Year of Release", int(movie->getYear()));
    oggettoJSon.insert("Image", QString::fromStdString(movie->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(movie->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione
    oggettoJSon.insert("Watched", movie->getWatched());
    oggettoJSon.insert("Starred", movie->getStarred());

    //Multimedia
    oggettoJSon.insert("Producer", QString::fromStdString(movie->getProducer()));
    oggettoJSon.insert("Platform", QString::fromStdString(movie->getPlatforms()));

    //Video
    oggettoJSon.insert("Duration", int(movie->getDuration()));
    oggettoJSon.insert("Prequel", QString::fromStdString(movie->getPrequel()->getTitle));
    oggettoJSon.insert("Sequel", QString::fromStdString(movie->getSequel()->getTitle));

    //specifiche del "Film"
    oggettoJSon.insert("Director", QString::fromStdString(movie->getDirector()));
    oggettoJSon.insert("Photo Director", QString::fromStdString(movie->getPhotoDirector()));
    //fine

    QJsonObject tipo;
    tipo.insert("Film", oggettoJSon);
    
    doc.setObject(tipo);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(Serie *serie){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Type", "Serie");
    oggettoJSon.insert("Title", QString::fromStdString(serie->getTitle()));
    oggettoJSon.insert("Genres", int(serie->getSubgenre()));
    oggettoJSon.insert("Description", QString::fromStdString(serie->getDescription()));
    oggettoJSon.insert("Year of Release", int(serie->getYear()));
    oggettoJSon.insert("Image", QString::fromStdString(serie->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(serie->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione
    oggettoJSon.insert("Watched", serie->getWatched());
    oggettoJSon.insert("Starred", serie->getStarred());

    //Multimedia
    oggettoJSon.insert("Producer", QString::fromStdString(serie->getProducer()));
    oggettoJSon.insert("Platform", QString::fromStdString(serie->getPlatforms()));

    //Video
    oggettoJSon.insert("Duration", int(serie->getDuration()));
    oggettoJSon.insert("Prequel", QString::fromStdString(serie->getPrequel()->getTitle));
    oggettoJSon.insert("Sequel", QString::fromStdString(serie->getSequel()->getTitle));

    //specifiche del "Serie"
    oggettoJSon.insert("Seasons", int(serie->getSeasons()));
    oggettoJSon.insert("Episodes", int(serie->getEpisodes()));
    oggettoJSon.insert("Creator", QString::fromStdString(serie->getCreator()));
    oggettoJSon.insert("Finished", serie->getFinished());
    //fine

    QJsonObject tipo;
    tipo.insert("Serie", oggettoJSon);
    
    doc.setObject(tipo);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(VideoGame *videogame){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;
    QJsonDocument doc;

    oggettoJSon.insert("Type", "Videogame");
    oggettoJSon.insert("Title", QString::fromStdString(videogame->getTitle()));
    oggettoJSon.insert("Genres", int(videogame->getSubgenre()));
    oggettoJSon.insert("Description", QString::fromStdString(videogame->getDescription()));
    oggettoJSon.insert("Year of Release", int(videogame->getYear()));
    oggettoJSon.insert("Image", QString::fromStdString(videogame->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(videogame->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione
    oggettoJSon.insert("Watched", videogame->getWatched());
    oggettoJSon.insert("Starred", videogame->getStarred());

    //Multimedia
    oggettoJSon.insert("Producer", QString::fromStdString(serie->getProducer()));
    oggettoJSon.insert("Platform", QString::fromStdString(serie->getPlatforms()));

    //specifiche del "Videogame"
    oggettoJSon.insert("Game Engine", QString::fromStdString(videogame->getGameEngine()));
    oggettoJSon.insert("Expected Hours Of Play", int(videogame->getExpectedHours()));
    //fine

    QJsonObject tipo;
    tipo.insert("Videogame", oggettoJSon);
    
    doc.setObject(tipo);
    libreria.write(doc.toJson());
    libreria.close();
};

/*
OTTIMIZZAZIONE

void insertContent(const Content& _content, QJsonObject& oggettoJSon){

    oggettoJSon.insert("Title", QString::fromStdString(_content->getTitle()));
    oggettoJSon.insert("Genres", int(_content->getSubgenre()));  
    oggettoJSon.insert("Description", QString::fromStdString(_content->getDescription()));
    oggettoJSon.insert("Year of Release", int(_content->getYear())); // Unsigned int da problemi di ambiguità
    oggettoJSon.insert("Image", QString::fromStdString(_content->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", QString::fromStdString(_content->getInspiration()->getTitle())); // Contiene il titolo dell'inspirazione
    oggettoJSon.insert("Watched", _content->getWatched());
    oggettoJSon.insert("Starred", _content->getStarred());

    //return oggettoJSon;
}

void insertPaper(const Paper& _paper, QJsonObject& oggettoJSon){
    insertContent(_paper, oggettoJSon);

    oggettoJSon.insert("Author", QString::fromStdString(_paper->getAuthor()));
    oggettoJSon.insert("Publisher", QString::fromStdString(_paper->getPublisher()));
    oggettoJSon.insert("Pages", int(_paper->getPages()));
    oggettoJSon.insert("Volume", int(_paper->getVolume()));

    //return oggettoJSon;

void insertMultimedia(const Multimedia& _multimedia, QJsonObject& oggettoJSon){
    insertContent(_multimedia, oggettoJSon);
    oggettoJSon.insert("Producer", QString::fromStdString(_multimedia->getProducer()));
    oggettoJSon.insert("Platform", QString::fromStdString(_multimedia->getPlatforms()));
}

void insertVideo(const Video& _video, QJsonObject& oggettoJSon){
    insertMultimedia(_video, oggettoJSon);
    oggettoJSon.insert("Duration", int(_video->getDuration()));
    oggettoJSon.insert("Prequel", QString::fromStdString(_video->getPrequel()->getTitle));
    oggettoJSon.insert("Sequel", QString::fromStdString(_video->getSequel()->getTitle));
}

}

*/
