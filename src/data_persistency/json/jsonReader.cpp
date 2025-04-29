#include "jsonReader.h"
#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"
#include "../../Model/lib/ScienceFictionLibrary.h"

ScienceFiction_Library* jsonReader::read(const string& filepath){

    ScienceFiction_Library& library = ScienceFiction_Library::getInstance();
    
    QFile jsonFile(QString::fromStdString(filepath));
    QString jsonString;
    if(jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        jsonString = jsonFile.readAll();
        jsonFile.close(); //chiudo il file dopo averlo letto

        QJsonParseError errorJ;
        QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &errorJ);
    
        if(errorJ.error != QJsonParseError::NoError){
            qDebug() << "Errore nel file : " << errorJ.errorString();
            return 0;
        }else{
            qDebug() << "Nessun errore";
        }

    }else{
        qWarning() << "Failed to open file";
        //!throw Exception;
        return 0;
    }

    QJsonDocument json_doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = json_doc.object();

    for(auto tipo : jsonObj.keys()){
        if(tipo == QString("Book")){
            QJsonArray innerArray = jsonObj.value(tipo).toArray();
            for(auto valore : jsonObj.value(tipo).toArray()){
                library.addContent(readBook(valore.toObject()));
            }
        }
        if(tipo == QString("Comic")){
            QJsonArray innerArray = jsonObj.value(tipo).toArray();
            for(auto valore : jsonObj.value(tipo).toArray()){
                library.addContent(readComic(valore.toObject()));
            } 
        }
        if(tipo == QString("Film")){
            QJsonArray innerArray = jsonObj.value(tipo).toArray();
            for(auto valore : jsonObj.value(tipo).toArray()){
                library.addContent(readFilm(valore.toObject()));
            } 
        }
        if(tipo == QString("Serie")){
            QJsonArray innerArray = jsonObj.value(tipo).toArray();
            for(auto valore : jsonObj.value(tipo).toArray()){
                library.addContent(readSerie(valore.toObject()));
            } 
        }
        if(tipo == QString("Videogame")){
            QJsonArray innerArray = jsonObj.value(tipo).toArray();
            for(auto valore : jsonObj.value(tipo).toArray()){
                library.addContent(readVideogame(valore.toObject()));
            } 
        }
    }   

    return &library;
};

Book* jsonReader::readBook(const QJsonObject& object){
    auto *libro = new Book();
    /*
    libro->setTitle(object.value("Title").toString().toStdString());
    libro->addSubgenre(object.value("Genres").toInt());
    libro->setDescription(object.value("Description").toString().toStdString());
    libro->setYear(object.value("Year of Release").toInt());
    libro->setImage(object.value("Image").toString().toStdString());
    libro->setInspiration(object.value("Inspiration").toInt());
    libro->setWatched(object.value("Watched").toBool());
    libro->setStarred(object.value("Starred").toBool());


    libro->setAuthor(object.value("Author").toString().toStdString());
    libro->setPublisher(object.value("Publisher").toString().toStdString());
    libro->setPages(object.value("Pages").toInt());
    libro->setVolume(object.value("Volume").toInt());
    */
    readPaper(libro, object);
    libro->setMainCharacter(object.value("Main Character").toString().toStdString());
    return libro;
}

Comic* jsonReader::readComic(const QJsonObject& object){
    auto *comic = new Comic();

    readPaper(comic, object);
    comic->setMainCharacter(object.value("Main Character").toString().toStdString());
    comic->setIllustrator(object.value("Illustrator").toString().toStdString());
    comic->setSerie(object.value("Series").toString().toStdString());
    comic->setFinished(object.value("Finished").toBool());
    return comic;
}

Film* jsonReader::readFilm(const QJsonObject& object){
    auto *film = new Film();

    readVideo(film, object);
    film->setDirector(object.value("Director").toString().toStdString());
    film->setPhotoDirector(object.value("Photo Director").toString().toStdString());
    return film;
}

Serie* jsonReader::readSerie(const QJsonObject& object){
    auto *serie = new Serie();

    readVideo(serie, object);
    serie->setSeasons(object.value("Seasons").toInt());
    serie->setEpisodes(object.value("Episodes").toInt());
    serie->setCreator(object.value("Creator").toString().toStdString());
    serie->setFinished(object.value("Finished").toBool());
    return serie;
}

VideoGame* jsonReader::readVideogame(const QJsonObject& object){
    auto *videogame = new VideoGame();

    readMultimedia(videogame, object);
    videogame->setGameEngine(object.value("Game Engine").toString().toStdString());
    videogame->setGameType(videogame->stringToGametype(object.value("Game Genre").toString().toStdString()));
    videogame->setExpectedHours(object.value("Expected Hours Of Play").toInt());
    return videogame;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/

void jsonReader::readContent(Content* content, const QJsonObject& object){
    content->setId(object.value("Id").toInt());
    content->setTitle(object.value("Title").toString().toStdString());
    content->addSubgenre(object.value("Genres").toInt());
    content->setDescription(object.value("Description").toString().toStdString());
    content->setYear(object.value("Year of Release").toInt());
    content->setImage(object.value("Image").toString().toStdString());
    content->setInspiration(object.value("Inspiration").toInt());
    content->setWatched(object.value("Watched").toBool());
    content->setStarred(object.value("Starred").toBool());
}

void jsonReader::readPaper(Paper* paper, const QJsonObject& object){
    readContent(paper, object);
    paper->setAuthor(object.value("Author").toString().toStdString());
    paper->setPublisher(object.value("Publisher").toString().toStdString());
    paper->setPages(object.value("Pages").toInt());
    paper->setVolume(object.value("Volume").toInt());
}

void jsonReader::readMultimedia(Multimedia* mult, const QJsonObject& object){
    readContent(mult, object);
    mult->setProducer(object.value("Producer").toString().toStdString());
    mult->setPlatforms(object.value("Platform").toString().toStdString());
}

void jsonReader::readVideo(Video* video, const QJsonObject& object){
    readMultimedia(video, object);
    video->setDuration(object.value("Duration").toInt());
    video->setPrequel(object.value("Prequel").toInt());
    video->setSequel(object.value("Sequel").toInt());
}

