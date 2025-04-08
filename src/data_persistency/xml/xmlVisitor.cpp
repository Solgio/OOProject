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
    QDomElement book_content=doc.createElement("Book");
    book_content.setAttribute("Title",QString::fromStdString(book->getTitle()));
    book_content.setAttribute("Subgenre",QString::number(book->getSubgenre()));
    book_content.setAttribute("Description",QString::fromStdString(book->getDescription()));
    book_content.setAttribute("Inspiration",QString::number(book->getInspiration()));
    book_content.setAttribute("Starred",QString::number(book->getStarred()));
    book_content.setAttribute("Watched",QString::number(book->getWatched()));
    book_content.setAttribute("Year",QString::number(book->getYear()));
    book_content.setAttribute("Image",QString::fromStdString(book->getImage()));
    book_content.setAttribute("Author",QString::fromStdString(book->getAuthor()));
    book_content.setAttribute("Publisher",QString::fromStdString(book->getPublisher()));
    book_content.setAttribute("Pages",QString::number(book->getPages()));
    book_content.setAttribute("Volume",QString::number(book->getVolume()));
    book_content.setAttribute("MainCharacter",QString::fromStdString(book->getMainCharacter()));
    root.appendChild(book_content);
};
void xmlVisitor::toXml(Comic *comic, QDomDocument& doc, QDomElement& root){
    QDomElement comic_content=doc.createElement("Comic");
    comic_content.setAttribute("Title",QString::fromStdString(comic->getTitle()));
    comic_content.setAttribute("Subgenre",QString::number(comic->getSubgenre()));
    comic_content.setAttribute("Description",QString::fromStdString(comic->getDescription()));
    comic_content.setAttribute("Inspiration",QString::number(comic->getInspiration()));
    comic_content.setAttribute("Starred",QString::number(comic->getStarred()));
    comic_content.setAttribute("Watched",QString::number(comic->getWatched()));
    comic_content.setAttribute("Year",QString::number(comic->getYear()));
    comic_content.setAttribute("Image",QString::fromStdString(comic->getImage()));
    comic_content.setAttribute("Author",QString::fromStdString(comic->getAuthor()));
    comic_content.setAttribute("Publisher",QString::fromStdString(comic->getPublisher()));
    comic_content.setAttribute("Pages",QString::number(comic->getPages()));
    comic_content.setAttribute("Volume",QString::number(comic->getVolume()));
    comic_content.setAttribute("MainCharacter",QString::fromStdString(comic->getMainCharacter()));
    comic_content.setAttribute("Illustrator",QString::fromStdString(comic->getIllustrator()));
    comic_content.setAttribute("Serie",QString::fromStdString(comic->getSerie()));
    comic_content.setAttribute("Finished",QString::number(comic->getFinished()));
    root.appendChild(comic_content);
};
void xmlVisitor::toXml(Film *film, QDomDocument& doc, QDomElement& root){
    QDomElement film_content=doc.createElement("Film");
    film_content.setAttribute("Title",QString::fromStdString(film->getTitle()));
    film_content.setAttribute("Subgenre",QString::number(film->getSubgenre()));
    film_content.setAttribute("Description",QString::fromStdString(film->getDescription()));
    film_content.setAttribute("Inspiration",QString::number(film->getInspiration()));
    film_content.setAttribute("Starred",QString::number(film->getStarred()));
    film_content.setAttribute("Watched",QString::number(film->getWatched()));
    film_content.setAttribute("Year",QString::number(film->getYear()));
    film_content.setAttribute("Image",QString::fromStdString(film->getImage()));
    film_content.setAttribute("Director",QString::fromStdString(film->getDirector()));
    film_content.setAttribute("Producer",QString::fromStdString(film->getProducer()));
    film_content.setAttribute("PhotoDirector",QString::fromStdString(film->getPhotoDirector()));
    film_content.setAttribute("Duration",QString::number(film->getDuration()));
    film_content.setAttribute("Platforms",QString::fromStdString(film->getPlatforms()));
    film_content.setAttribute("Prequel",QString::number(film->getPrequel()));
    film_content.setAttribute("Sequel",QString::number(film->getSequel()));
    root.appendChild(film_content);
};
void xmlVisitor::toXml(Serie *serie, QDomDocument& doc, QDomElement& root){
    QDomElement serie_content=doc.createElement("Serie");
    serie_content.setAttribute("Title",QString::fromStdString(serie->getTitle()));
    serie_content.setAttribute("Subgenre",QString::number(serie->getSubgenre()));
    serie_content.setAttribute("Description",QString::fromStdString(serie->getDescription()));
    serie_content.setAttribute("Inspiration",QString::number(serie->getInspiration()));
    serie_content.setAttribute("Starred",QString::number(serie->getStarred()));
    serie_content.setAttribute("Watched",QString::number(serie->getWatched()));
    serie_content.setAttribute("Year",QString::number(serie->getYear()));
    serie_content.setAttribute("Image",QString::fromStdString(serie->getImage()));
    serie_content.setAttribute("Creator",QString::fromStdString(serie->getCreator()));
    serie_content.setAttribute("Producer",QString::fromStdString(serie->getProducer()));
    serie_content.setAttribute("Platform",QString::fromStdString(serie->getPlatforms()));
    serie_content.setAttribute("Duration",QString::number(serie->getDuration()));
    serie_content.setAttribute("Prequel",QString::number(serie->getPrequel()));
    serie_content.setAttribute("Sequel",QString::number(serie->getSequel()));
    serie_content.setAttribute("Seasons",QString::number(serie->getSeasons()));
    serie_content.setAttribute("Episodes",QString::number(serie->getEpisodes()));
    serie_content.setAttribute("Finished",QString::number(serie->getFinished())); 
    root.appendChild(serie_content);   
};
void xmlVisitor::toXml(VideoGame *videogame, QDomDocument& doc, QDomElement& root){
    QDomElement videogame_content=doc.createElement("VideoGame");
    videogame_content.setAttribute("Title",QString::fromStdString(videogame->getTitle()));
    videogame_content.setAttribute("Subgenre",QString::number(videogame->getSubgenre()));
    videogame_content.setAttribute("Description",QString::fromStdString(videogame->getDescription()));
    videogame_content.setAttribute("Inspiration",QString::number(videogame->getInspiration()));
    videogame_content.setAttribute("Starred",QString::number(videogame->getStarred()));
    videogame_content.setAttribute("Watched",QString::number(videogame->getWatched()));
    videogame_content.setAttribute("Year",QString::number(videogame->getYear()));
    videogame_content.setAttribute("Image",QString::fromStdString(videogame->getImage()));
    videogame_content.setAttribute("Producer",QString::fromStdString(videogame->getProducer()));
    videogame_content.setAttribute("Platform",QString::fromStdString(videogame->getPlatforms()));
    videogame_content.setAttribute("GameEngine",QString::fromStdString(videogame->getGameEngine()));
    videogame_content.setAttribute("ExpectedHours",QString::number(videogame->getExpectedHours()));
    root.appendChild(videogame_content);
};