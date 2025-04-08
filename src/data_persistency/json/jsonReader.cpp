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
            return;
        }else{
            qDebug() << "Nessun errore";
        }

    }else{
        qWarning() << "Failed to open file";
        //throw Exception;
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
};

Book* jsonReader::readBook(const QJsonObject& object) const{
    Book *libro = new Book();
    libro->setTitle(object.value("Title").toString().toStdString());
    //libro->hasSubgenre(); //!WTF
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
}

Comic* jsonReader::readComic(const QJsonObject& object) const{

}

Film* jsonReader::readFilm(const QJsonObject& object) const{

}

Serie* jsonReader::readSerie(const QJsonObject& object) const{

}

VideoGame* jsonReader::readVideogame(const QJsonObject& object) const{

}