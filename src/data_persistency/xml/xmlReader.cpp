#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <vector>
#include "xmlReader.h"
#include "../../Model/lib/ScienceFictionLibrary.h"
#include "../../Model/lib/Content.h"
#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"
using std::vector, std::string;

void xmlReader::commonReader(Content* content, QXmlStreamReader& object) const{
    QXmlStreamReader::TokenType token = object.readNext();
    if (token == QXmlStreamReader::StartElement) {
        if (object.name() == "Title") {
            content->setTitle((object.readElementText()).toStdString());
        }
        else if (object.name() == "Description") {
            content->setDescription((object.readElementText()).toStdString());
        }
        else if (object.name() == "Starred") {
            content->setStarred(object.readElementText().toInt());
        }
        else if (object.name() == "Watched") {
            content->setWatched(object.readElementText().toInt());
        }
        else if (object.name() == "Year") {
            content->setYear(object.readElementText().toUInt());
        }
        else if (object.name() == "Image") {
            content->setImage((object.readElementText()).toStdString());
        }
        /*
        else if (object.name() == "Subgenre") {
            content->addSubgenre(object.readElementText());
        }*/
    }
}
void xmlReader::paperReader(Paper* content, QXmlStreamReader& object) const{
    commonReader(content, object);
    QXmlStreamReader::TokenType token = object.readNext();
    if (token == QXmlStreamReader::StartElement) {
        if (object.name() == "Author") {
            content->setAuthor((object.readElementText()).toStdString());
        }
        else if (object.name() == "Publisher") {
            content->setPublisher((object.readElementText()).toStdString());
        }
        else if (object.name() == "Pages") {
            content->setPages(object.readElementText().toUInt());
        }
        else if (object.name() == "Volume") {
            content->setVolume(object.readElementText().toUInt());
        }
    }
}
void xmlReader::multimediaReader(Multimedia* content, QXmlStreamReader& object) const{
    commonReader(content, object);
    QXmlStreamReader::TokenType token = object.readNext();
    if (token == QXmlStreamReader::StartElement) {
        if (object.name() == "Producer") {
            content->setProducer((object.readElementText()).toStdString());
        }
        else if (object.name() == "Platforms") {
            content->setPlatforms((object.readElementText()).toStdString());
        }
    }
}
void xmlReader::videoReader(Video* content, QXmlStreamReader& object) const{
    multimediaReader(content, object);
    QXmlStreamReader::TokenType token = object.readNext();
    if (token == QXmlStreamReader::StartElement) {
        if (object.name() == "Producer") {
            content->setDuration((object.readElementText()).toUInt());
        }/*
        else if(object.name()=="Prequel"){}
        else if(object.name()=="Prequel"){}*/
        
    }
}

Book* xmlReader::readBook(QXmlStreamReader& object) const{
    Book* book = new Book();
    paperReader(book, object);
    while (!(object.isEndElement() && object.name() == "Book")) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == "MainCharacter") {
                book->setMainCharacter((object.readElementText()).toStdString());
            }    
        }
    }
    return book;
}
Comic* xmlReader::readComic(QXmlStreamReader& object) const{
    Comic* comic = new Comic();
    paperReader(comic, object);
    while (!(object.isEndElement() && object.name() == "Comic")) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == "MainCharacter") {
                comic->setMainCharacter((object.readElementText()).toStdString());
            }
            else if (object.name() == "Illustrator") {
                comic->setIllustrator((object.readElementText()).toStdString());
            }
            else if(object.name() == "Serie"){
                comic->setSerie((object.readElementText()).toStdString());
            }
            else if(object.name() == "Finished"){
                comic->setFinished(object.readElementText().toUInt());
            }
        }
    }
    return comic;
}
Film* xmlReader::readFilm(QXmlStreamReader& object) const{
    Film* movie = new Film();
    videoReader(movie, object);
    while (!(object.isEndElement() && object.name() == "Film")) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == "Director") {
                movie->setDirector((object.readElementText()).toStdString());
            }
            else if (object.name() == "PhotoDirector") {
                movie->setPhotoDirector((object.readElementText()).toStdString());
            }
        }
    }
    return movie;
}
Serie* xmlReader::readSerie(QXmlStreamReader& object) const{
    Serie* serie = new Serie();
    videoReader(serie, object);
    while (!(object.isEndElement() && object.name() == "Serie")) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == "Seasons") {
                serie->setSeasons((object.readElementText()).toUInt());
            }
            else if (object.name() == "Episodes") {
                serie->setEpisodes((object.readElementText()).toUInt());
            }
            else if (object.name() == "Creator") {
                serie->setCreator(object.readElementText().toStdString());
            }
            else if (object.name() == "Finished") {
                serie->setFinished(object.readElementText().toUInt());
            }
        }
    }
    return serie;
}
VideoGame* xmlReader::readVideoGame(QXmlStreamReader& object) const{
    VideoGame* videogame = new VideoGame();
    multimediaReader(videogame, object);
    while (!(object.isEndElement() && object.name() == "VideoGame")) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == "GameEngine") {
                videogame->setGameEngine((object.readElementText()).toStdString());
            }
            else if (object.name() == "ExpectedHours") {
                videogame->setExpectedHours((object.readElementText()).toUInt());
            }
        }
    }
    return videogame;
}



ScienceFiction_Library* xmlReader::read(const string& filepath){
    
    QFile file(QString::fromStdString(filepath));

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "Failed to open file for writing";
        //! Forse qui è meglio un'eccezione   
        file.close();
           
    }

    // Clear the library before loading new data
    ScienceFiction_Library& library = ScienceFiction_Library::getInstance();
    
    QXmlStreamReader xmlreader(&file);
    while (!xmlreader.atEnd() && !xmlreader.hasError()) {
        QXmlStreamReader::TokenType token = xmlreader.readNext();
        
        if (token == QXmlStreamReader::StartElement) {
            if (xmlreader.name() == "Book") {
                library.addContent(readBook(xmlreader));
            }
            else if (xmlreader.name() == "Comic") {
                library.addContent(readComic(xmlreader));
            }
            else if (xmlreader.name() == "Film") {
                library.addContent(readFilm(xmlreader));
            }
            else if (xmlreader.name() == "Serie") {
                library.addContent(readSerie(xmlreader));
            }
            else if (xmlreader.name() == "VideoGame") {
                library.addContent(readVideoGame(xmlreader));
            }
            else {
                xmlreader.raiseError(QObject::tr("Not a valid content type"));
            }
        }
    }

    if (xmlreader.hasError()) {
        qWarning() << "XML error:" << xmlreader.errorString();
        //clearLibrary();
        
    }

    file.close();
    return &library;
 }