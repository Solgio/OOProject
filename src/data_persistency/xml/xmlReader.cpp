#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <vector>
#include <stdexcept>
#include "xmlReader.h"
#include "../../Model/lib/ScienceFictionLibrary.h"
#include "../../Model/lib/Video.h"
#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"
using std::vector, std::string;

void xmlReader::commonReader(Content* content, QXmlStreamReader& object) const{
    while (!object.atEnd() && !object.hasError()) {
        QXmlStreamReader::TokenType token = object.readNext();
        
        if (token == QXmlStreamReader::EndElement) {
            break;
        }

        if (token == QXmlStreamReader::StartElement) {
            if(object.name()==QString("Id")){
                content->setId(object.readElementText().toUInt());
            }
            else if (object.name() == QString("Title")) {
                content->setTitle((object.readElementText()).toStdString());
            }
            else if (object.name() == QString("Description")) {
                content->setDescription((object.readElementText()).toStdString());
            }
            else if(object.name()== QString("Inspiration")){
                content->setInspiration(object.readElementText().toInt());
            }
            else if (object.name() == QString("Starred")) {
                content->setStarred(object.readElementText().toInt());
            }
            else if (object.name() == QString("Watched")) {
                content->setWatched(object.readElementText().toInt());
            }
            else if (object.name() == QString("Year")) {
                content->setYear(object.readElementText().toUInt());
            }
            else if (object.name() == QString("Image")) {
                content->setImage((object.readElementText()).toStdString());
            }
            else if (object.name() == QString("Subgenre")) {
                content->addSubgenre(object.readElementText().toUInt());
                return;
            }
        }
    }
}
void xmlReader::paperReader(Paper* content, QXmlStreamReader& object) const{
    commonReader(content, object);
    
    while (!object.atEnd() && !object.hasError()) {
        QXmlStreamReader::TokenType token = object.readNext();
        
        if (token == QXmlStreamReader::EndElement) {
            break;
        }

        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == QString("Author")) {
                content->setAuthor((object.readElementText()).toStdString());
            }
            else if (object.name() == QString("Publisher")) {
                content->setPublisher((object.readElementText()).toStdString());
            }
            else if (object.name() == QString("Pages")) {
                content->setPages(object.readElementText().toUInt());
            }
            else if (object.name() == QString("Volume")) {
                content->setVolume(object.readElementText().toUInt());
                return;
            }
        }
    }
}
void xmlReader::multimediaReader(Multimedia* content, QXmlStreamReader& object) const{
    commonReader(content, object);

    while (!object.atEnd() && !object.hasError()) {
        QXmlStreamReader::TokenType token = object.readNext();
        
        if (token == QXmlStreamReader::EndElement) {
            break;
        }

        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == QString("Producer")) {
                content->setProducer((object.readElementText()).toStdString());
            }
            else if (object.name() == QString("Platforms")) {
                content->setPlatforms((object.readElementText()).toStdString());
                return;
            }
        }
    }
}
void xmlReader::videoReader(Video* content, QXmlStreamReader& object) const{
    multimediaReader(content, object);
    
    while (!object.atEnd() && !object.hasError()) {
        QXmlStreamReader::TokenType token = object.readNext();
        
        if (token == QXmlStreamReader::EndElement) {
            break;
        }

        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == QString("Duration")) {
                content->setDuration((object.readElementText()).toUInt());
            }
            else if(object.name()==QString("Prequel")){
                content->setPrequel(object.readElementText().toUInt());
            }
            else if(object.name()==QString("Sequel")){
                content->setSequel(object.readElementText().toUInt());
                return;
            }        
        }
    }
}

unique_ptr<Book> xmlReader::readBook(QXmlStreamReader& object) const{
    auto book = make_unique<Book>();
    paperReader(book.get(), object);
    while (!(object.isEndElement() && object.name() == QString("Book"))) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == QString("MainCharacter")) {
                book->setMainCharacter((object.readElementText()).toStdString());
            }    
        }
    }
    return book;
}
unique_ptr<Comic> xmlReader::readComic(QXmlStreamReader& object) const{
    auto comic = make_unique<Comic>();
    paperReader(comic.get(), object);
    while (!(object.isEndElement() && object.name() == QString("Comic"))) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == QString("MainCharacter")) {
                comic->setMainCharacter((object.readElementText()).toStdString());
            }
            else if (object.name() == QString("Illustrator")) {
                comic->setIllustrator((object.readElementText()).toStdString());
            }
            else if(object.name() == QString("Serie")){
                comic->setSerie((object.readElementText()).toStdString());
            }
            else if(object.name() == QString("Finished")){
                comic->setFinished(object.readElementText().toUInt());
            }
        }
    }
    return comic;
}
unique_ptr<Film> xmlReader::readFilm(QXmlStreamReader& object) const{
    auto movie = make_unique<Film>();
    videoReader(movie.get(), object);
    while (!(object.isEndElement() && object.name() == QString("Film"))) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == QString("Director")) {
                movie->setDirector((object.readElementText()).toStdString());
            }
            else if (object.name() == QString("PhotoDirector")) {
                movie->setPhotoDirector((object.readElementText()).toStdString());
            }
        }
    }
    return movie;
}
unique_ptr<Serie> xmlReader::readSerie(QXmlStreamReader& object) const{
    auto serie = make_unique<Serie>();
    videoReader(serie.get(), object);
    while (!(object.isEndElement() && object.name() == QString("Serie"))) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == QString("Seasons")) {
                serie->setSeasons((object.readElementText()).toUInt());
            }
            else if (object.name() == QString("Episodes")) {
                serie->setEpisodes((object.readElementText()).toUInt());
            }
            else if (object.name() == QString("Creator")) {
                serie->setCreator(object.readElementText().toStdString());
            }
            else if (object.name() == QString("Finished")) {
                serie->setFinished(object.readElementText().toUInt());
            }
        }
    }
    return serie;
}
unique_ptr<VideoGame> xmlReader::readVideoGame(QXmlStreamReader& object) const{
    auto videogame = make_unique<VideoGame>();
    multimediaReader(videogame.get(), object);
    while (!(object.isEndElement() && object.name() == QString("VideoGame"))) {
        QXmlStreamReader::TokenType token = object.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (object.name() == QString("GameEngine")) {
                videogame->setGameEngine((object.readElementText()).toStdString());
            }
            else if(object.name()== QString("GameType")){
                videogame->setGameType(videogame->stringToGametype((object.readElementText()).toStdString()));
            }
            else if (object.name() == QString("Platforms")) {
                videogame->setPlatforms((object.readElementText()).toStdString());
            }
            else if (object.name() == QString("ExpectedHours")) {
                videogame->setExpectedHours((object.readElementText()).toUInt());
            }
        }
    }
    return videogame;
}



ScienceFiction_Library* xmlReader::read(const string& filepath){
    
    QFile file(QString::fromStdString(filepath));
    try{
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            throw std::invalid_argument("Failed to open file: " + file.errorString().toStdString());
        }
    }
    catch(const std::invalid_argument& e) {
        qWarning() << "The provided file cannot be opened" << e.what();
        return nullptr;
    }

    // Clear the library before loading new data
    ScienceFiction_Library& library = ScienceFiction_Library::getInstance();
    
    QXmlStreamReader xmlreader(&file);
    try{
        while (!xmlreader.atEnd() && !xmlreader.hasError()) {
            QXmlStreamReader::TokenType token = xmlreader.readNext();
            QString xmlName=xmlreader.name().toString();
            
            if (token == QXmlStreamReader::StartElement) {
                if (xmlName == "Book") {
                    library.addContent(readBook(xmlreader).release());
                }
                else if (xmlName == "Comic") {
                    library.addContent(readComic(xmlreader).release());
                }
                else if (xmlName == "Film") {
                    library.addContent(readFilm(xmlreader).release());
                }
                else if (xmlName == "Serie") {
                    library.addContent(readSerie(xmlreader).release());
                }
                else if (xmlName == "VideoGame") {
                    library.addContent(readVideoGame(xmlreader).release());
                }
            }
        }
    } catch(const std::invalid_argument& e) {
        qWarning() << "XML parsing error,:" << e.what()<<"\nCheck that the file only contains approved tags";

        file.close();
        return nullptr;    
    }

    file.close();
    return &library;
 }