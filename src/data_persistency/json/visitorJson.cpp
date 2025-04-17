#include "visitorJson.h"

#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"


void VisitorJson::setLibreria(QString path){
    if(libreria.open(QIODevice::ReadOnly)){
        libreria.close();
    }
    libreria.setFileName(path);
}

VisitorJson::VisitorJson(){};

VisitorJson::VisitorJson(QString filePath):libreria(filePath){
    libreria.open(QIODevice::WriteOnly);

    QByteArray contentFile;
    contentFile = libreria.readAll();

    QJsonParseError errorJ;
    QJsonDocument doc = QJsonDocument::fromJson(contentFile, &errorJ);

    if(errorJ.error != QJsonParseError::NoError){
        qDebug() << "Errore nel file : " << errorJ.errorString();
        qDebug() << "Azzero il file json";
        libreria.resize(0);
        QJsonObject emptyObject;
        QJsonDocument emptyDoc(emptyObject);
        libreria.write(emptyDoc.toJson());
        qDebug() << "Creo JsonObject vuoto";
        libreria.close();
    }else{
        qDebug() << "Nessun errore";
    }
};



void VisitorJson::toFileJson(const Book* book){

    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto

    QByteArray contentFile;
    contentFile = libreria.readAll();

    QJsonParseError errorJ;
    QJsonDocument doc = QJsonDocument::fromJson(contentFile, &errorJ);

    if(errorJ.error != QJsonParseError::NoError){
        qDebug() << "Errore nel file : " << errorJ.errorString();
        libreria.close();
        return;
    }else{
        qDebug() << "Nessun errore";
    }

    QJsonObject jsonLetto;
    jsonLetto = doc.object();

    QJsonArray arrayBook;
    if(jsonLetto.contains("Book")){
        jsonLetto["Book"] = arrayBook;
    }else{
        arrayBook = jsonLetto.value("Book").toArray();
    }

    QJsonObject oggettoJSon;
    insertPaper(book, oggettoJSon); //contiene anche insertContent(...);
    //specifiche del "Book"
    oggettoJSon.insert("Main Character", QString::fromStdString(book->getMainCharacter()));
    //fine

    arrayBook.append(oggettoJSon);
    
    doc.setObject(jsonLetto);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(const Comic* comic){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto

    QByteArray contentFile;
    contentFile = libreria.readAll();

    QJsonParseError errorJ;
    QJsonDocument doc = QJsonDocument::fromJson(contentFile, &errorJ);

    if(errorJ.error != QJsonParseError::NoError){
        qDebug() << "Errore nel file : " << errorJ.errorString();
        libreria.close();
        return;
    }else{
        qDebug() << "Nessun errore";
    }

    QJsonObject jsonLetto;
    jsonLetto = doc.object();

    QJsonArray arrayBook;
    if(jsonLetto.contains("Comic")){
        jsonLetto["Comic"] = arrayBook;
    }else{
        arrayBook = jsonLetto.value("Comic").toArray();
    }

    QJsonObject oggettoJSon;
    insertPaper(comic, oggettoJSon);
    //Book
    oggettoJSon.insert("Main Character", QString::fromStdString(comic->getMainCharacter()));
    //specifiche del "Comic"
    oggettoJSon.insert("Illustrator", QString::fromStdString(comic->getIllustrator()));
    oggettoJSon.insert("Series", QString::fromStdString(comic->getSerie()));
    oggettoJSon.insert("Finished", comic->getFinished());
    //fine

    arrayBook.append(oggettoJSon);
    
    doc.setObject(jsonLetto);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(const Film* movie){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    
    QByteArray contentFile;
    contentFile = libreria.readAll();

    QJsonParseError errorJ;
    QJsonDocument doc = QJsonDocument::fromJson(contentFile, &errorJ);

    if(errorJ.error != QJsonParseError::NoError){
        qDebug() << "Errore nel file : " << errorJ.errorString();
        libreria.close();
        return;
    }else{
        qDebug() << "Nessun errore";
    }

    QJsonObject jsonLetto;
    jsonLetto = doc.object();

    QJsonArray arrayBook;
    if(jsonLetto.contains("Film")){
        jsonLetto["Film"] = arrayBook;
    }else{
        arrayBook = jsonLetto.value("Film").toArray();
    }

    QJsonObject oggettoJSon;
    insertVideo(movie, oggettoJSon);
    //specifiche del "Film"
    oggettoJSon.insert("Director", QString::fromStdString(movie->getDirector()));
    oggettoJSon.insert("Photo Director", QString::fromStdString(movie->getPhotoDirector()));
    //fine

    arrayBook.append(oggettoJSon);
    
    doc.setObject(jsonLetto);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(const Serie* serie){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    
    QByteArray contentFile;
    contentFile = libreria.readAll();

    QJsonParseError errorJ;
    QJsonDocument doc = QJsonDocument::fromJson(contentFile, &errorJ);

    if(errorJ.error != QJsonParseError::NoError){
        qDebug() << "Errore nel file : " << errorJ.errorString();
        libreria.close();
        return;
    }else{
        qDebug() << "Nessun errore";
    }

    QJsonObject jsonLetto;
    jsonLetto = doc.object();

    QJsonArray arrayBook;
    if(jsonLetto.contains("Serie")){
        jsonLetto["Serie"] = arrayBook;
    }else{
        arrayBook = jsonLetto.value("Serie").toArray();
    }

    QJsonObject oggettoJSon;
    insertVideo(serie, oggettoJSon);
    //specifiche del "Serie"
    oggettoJSon.insert("Seasons", int(serie->getSeasons()));
    oggettoJSon.insert("Episodes", int(serie->getEpisodes()));
    oggettoJSon.insert("Creator", QString::fromStdString(serie->getCreator()));
    oggettoJSon.insert("Finished", serie->getFinished());
    //fine

    arrayBook.append(oggettoJSon);
    
    doc.setObject(jsonLetto);
    libreria.write(doc.toJson());
    libreria.close();
};


void VisitorJson::toFileJson(const VideoGame *videogame){
    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto

    QByteArray contentFile;
    contentFile = libreria.readAll();

    QJsonParseError errorJ;
    QJsonDocument doc = QJsonDocument::fromJson(contentFile, &errorJ);

    if(errorJ.error != QJsonParseError::NoError){
        qDebug() << "Errore nel file : " << errorJ.errorString();
        libreria.close();
        return;
    }else{
        qDebug() << "Nessun errore";
    }

    QJsonObject jsonLetto;
    jsonLetto = doc.object();

    QJsonArray arrayBook;
    if(jsonLetto.contains("Videogame")){
        jsonLetto["Videogame"] = arrayBook;
    }else{
        arrayBook = jsonLetto.value("Videogame").toArray();
    }
    
    QJsonObject oggettoJSon;
    insertMultimedia(videogame, oggettoJSon);
    //specifiche del "Videogame"
    oggettoJSon.insert("Game Engine", QString::fromStdString(videogame->getGameEngine()));
    oggettoJSon.insert("Game Genre", QString::fromStdString(videogame->getGameType()));
    oggettoJSon.insert("Expected Hours Of Play", int(videogame->getExpectedHours()));
    //fine

    arrayBook.append(oggettoJSon);
    
    doc.setObject(jsonLetto);
    libreria.write(doc.toJson());
    libreria.close();
};



 void VisitorJson::insertContent(const Content* _content, QJsonObject& oggettoJSon){

    oggettoJSon.insert("Id", int(_content->getId()));
    oggettoJSon.insert("Title", QString::fromStdString(_content->getTitle()));
    oggettoJSon.insert("Genres", int(_content->getSubgenre()));  
    oggettoJSon.insert("Description", QString::fromStdString(_content->getDescription()));
    oggettoJSon.insert("Year of Release", int(_content->getYear())); // Unsigned int da problemi di ambiguità
    oggettoJSon.insert("Image", QString::fromStdString(_content->getImage())); // contiene la image path
    oggettoJSon.insert("Inspiration", int(_content->getInspiration()));
    oggettoJSon.insert("Watched", _content->getWatched());
    oggettoJSon.insert("Starred", _content->getStarred());

    //return oggettoJSon;
}

void VisitorJson::insertPaper(const Paper* _paper, QJsonObject& oggettoJSon){
    insertContent(_paper, oggettoJSon);

    oggettoJSon.insert("Author", QString::fromStdString(_paper->getAuthor()));
    oggettoJSon.insert("Publisher", QString::fromStdString(_paper->getPublisher()));
    oggettoJSon.insert("Pages", int(_paper->getPages()));
    oggettoJSon.insert("Volume", int(_paper->getVolume()));

}

void VisitorJson::insertMultimedia(const Multimedia* _multimedia, QJsonObject& oggettoJSon){
    insertContent(_multimedia, oggettoJSon);
    oggettoJSon.insert("Producer", QString::fromStdString(_multimedia->getProducer()));
    oggettoJSon.insert("Platform", QString::fromStdString(_multimedia->getPlatforms()));
}

void VisitorJson::insertVideo(const Video* _video, QJsonObject& oggettoJSon){
    insertMultimedia(_video, oggettoJSon);
    oggettoJSon.insert("Duration", int(_video->getDuration()));
    oggettoJSon.insert("Prequel", int(_video->getPrequel()));
    oggettoJSon.insert("Sequel", int(_video->getSequel()));
}
