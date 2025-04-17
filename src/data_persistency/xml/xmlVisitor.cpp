#include <QtCore>
#include <QtXml>
#include <QDebug>
#include "xmlVisitor.h"
#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"

void xmlVisitor::toXml(Book *book, QDomDocument& doc, QDomElement& root){
    QDomElement bookElem=doc.createElement("Book");

    commonTags(book, doc, bookElem);
    paperTags(book, doc, bookElem);
    
    addElement(doc, bookElem, "MainCharacter", QString::fromStdString(book->getMainCharacter()));
    root.appendChild(bookElem);
};
void xmlVisitor::toXml(Comic *comic, QDomDocument& doc, QDomElement& root){
    QDomElement comicElem=doc.createElement("Comic");

    commonTags(comic, doc, comicElem);
    paperTags(comic, doc, comicElem);
    
    addElement(doc, comicElem, "MainCharacter", QString::fromStdString(comic->getMainCharacter()));
    addElement(doc, comicElem, "Illustrator", QString::fromStdString(comic->getIllustrator()));
    addElement(doc, comicElem, "Serie", QString::fromStdString(comic->getSerie()));
    addElement(doc, comicElem, "Finished", QString::number(comic->getFinished()));
    root.appendChild(comicElem);
};
void xmlVisitor::toXml(Film *film, QDomDocument& doc, QDomElement& root){
    QDomElement filmElem=doc.createElement("Film");
    
    commonTags(film, doc, filmElem);
    multimediaTags(film, doc, filmElem);
    videoTags(film, doc, filmElem);
      
    addElement(doc, filmElem, "Director", QString::fromStdString(film->getDirector()));
    addElement(doc, filmElem, "PhotoDirector", QString::fromStdString(film->getPhotoDirector()));
    root.appendChild(filmElem);
};
void xmlVisitor::toXml(Serie *serie, QDomDocument& doc, QDomElement& root){
    QDomElement serieElem=doc.createElement("Serie");

    commonTags(serie, doc, serieElem);
    multimediaTags(serie, doc, serieElem);
    videoTags(serie, doc, serieElem);
   
    addElement(doc, serieElem, "Seasons", QString::number(serie->getSeasons()));
    addElement(doc, serieElem, "Episodes", QString::number(serie->getEpisodes()));
    addElement(doc, serieElem, "Creator", QString::fromStdString(serie->getCreator()));
    addElement(doc, serieElem, "Finished", QString::number(serie->getFinished()));
    root.appendChild(serieElem);   
};
void xmlVisitor::toXml(VideoGame *videogame, QDomDocument& doc, QDomElement& root){
    QDomElement videogameElem=doc.createElement("VideoGame");

    commonTags(videogame, doc, videogameElem);
    multimediaTags(videogame, doc, videogameElem);
    
    addElement(doc, videogameElem, "GameEngine", QString::fromStdString(videogame->getGameEngine()));
    addElement(doc, videogameElem, "GameType", QString::number(videogame->getGameTypeEnum()));
    addElement(doc, videogameElem, "ExpectedHours", QString::number(videogame->getExpectedHours()));
    root.appendChild(videogameElem);
};

void xmlVisitor::commonTags(Content *content, QDomDocument& doc, QDomElement& contentElem){
    addElement(doc, contentElem, "Id", QString::number(content->getId()));
    addElement(doc, contentElem, "Title", QString::fromStdString(content->getTitle()));
    addElement(doc, contentElem, "Description", QString::fromStdString(content->getDescription()));
    addElement(doc, contentElem, "Inspiration", QString::number(content->getInspiration()));
    addElement(doc, contentElem, "Starred", QString::number(content->getStarred()));
    addElement(doc, contentElem, "Watched", QString::number(content->getWatched()));
    addElement(doc, contentElem, "Year", QString::number(content->getYear()));
    addElement(doc, contentElem, "Image", QString::fromStdString(content->getImage()));
    addElement(doc, contentElem, "Subgenre", QString::number(content->getSubgenre()));
}
void xmlVisitor::paperTags(Paper *content, QDomDocument& doc, QDomElement& paperElem){
    addElement(doc, paperElem, "Author", QString::fromStdString(content->getAuthor()));
    addElement(doc, paperElem, "Publisher", QString::fromStdString(content->getPublisher()));
    addElement(doc, paperElem, "Pages", QString::number(content->getPages()));
    addElement(doc, paperElem, "Volume", QString::number(content->getVolume()));
}
void xmlVisitor::multimediaTags(Multimedia *content, QDomDocument& doc, QDomElement& multimediaElem){
    addElement(doc, multimediaElem, "Producer", QString::fromStdString(content->getProducer()));
    addElement(doc, multimediaElem, "Platforms", QString::fromStdString(content->getPlatforms()));
}
void xmlVisitor::videoTags(Video *content, QDomDocument& doc, QDomElement& videoElem){
    addElement(doc, videoElem, "Duration", QString::number(content->getDuration()));
    addElement(doc, videoElem, "Prequel", QString::number(content->getPrequel()));
    addElement(doc, videoElem, "Sequel", QString::number(content->getSequel()));
}

void xmlVisitor::addElement(QDomDocument& doc, QDomElement& parent, const QString& name, const QString& value) {
    QDomElement elem = doc.createElement(name);
    QDomText text = doc.createTextNode(value);
    elem.appendChild(text);
    parent.appendChild(elem);
}