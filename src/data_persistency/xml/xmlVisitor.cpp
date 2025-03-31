#include <QtCore>
#include <QtXml>
#include <QDebug>
#include "xmlVisitor.h"
#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"

void xmlVisitor::toXml(Book *book){
    QDomDocument document;
    QDomElement book_content=document.createElement("Book");
    book_content.setAttribute("Title",QString::fromStdString(book->getTitle()));
    book_content.setAttribute("Description",QString::fromStdString(book->getDescription()));
    book_content.setAttribute("Starred",QString::number(book->getStarred()));
    book_content.setAttribute("Watched",QString::number(book->getWatched()));
    book_content.setAttribute("Year",QString::number(book->getYear()));
    book_content.setAttribute("Image",QString::fromStdString(book->getImage()));
    book_content.setAttribute("Author",QString::fromStdString(book->getAuthor()));
    book_content.setAttribute("Publisher",QString::fromStdString(book->getPublisher()));
    book_content.setAttribute("Pages",QString::number(book->getPages()));
    book_content.setAttribute("Volume",QString::number(book->getVolume()));
    book_content.setAttribute("MainCharacter",QString::fromStdString(book->getMainCharacter()));
    //!CERCARE METODO DA POINTER A STRINGA O QPOINTER
    //book_content.setAttribute("Inspiration",QString::fromStdString(book->getInspiration()));
    book_content.setAttribute("Subgenre",QString::number(book->getSubgenre()));
    document.appendChild(book_content);
};
void xmlVisitor::toXml(Comic *comic){
    QDomDocument document;
    QDomElement comic_content=document.createElement("Comic");
    comic_content.setAttribute("Title",QString::fromStdString(comic->getTitle()));
    comic_content.setAttribute("Description",QString::fromStdString(comic->getDescription()));
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
    //!CERCARE METODO DA POINTER A STRINGA O QPOINTER
    //comic_content.setAttribute("Inspiration",QString::fromStdString(comic->getInspiration()));
    comic_content.setAttribute("Subgenre",QString::number(comic->getSubgenre()));
    document.appendChild(comic_content);
};
void xmlVisitor::toXml(Film *film){
    QDomDocument document;
    QDomElement film_content=document.createElement("Film");
    film_content.setAttribute("Title",QString::fromStdString(film->getTitle()));
    film_content.setAttribute("Description",QString::fromStdString(film->getDescription()));
    film_content.setAttribute("Starred",QString::number(film->getStarred()));
    film_content.setAttribute("Watched",QString::number(film->getWatched()));
    film_content.setAttribute("Year",QString::number(film->getYear()));
    film_content.setAttribute("Image",QString::fromStdString(film->getImage()));
    film_content.setAttribute("Director",QString::fromStdString(film->getDirector()));
    film_content.setAttribute("Producer",QString::fromStdString(film->getProducer()));
    film_content.setAttribute("PhtoDirector",QString::fromStdString(film->getPhotoDirector()));
    film_content.setAttribute("Duration",QString::number(film->getDuration()));
    film_content.setAttribute("Platform",QString::fromStdString(film->getPlatforms()));
    
    //!CERCARE METODO DA POINTER A STRINGA O QPOINTER
    //film_content.setAttribute("Prequel",QString::fromStdString(film->getPrequel()));
    //film_content.setAttribute("Sequel",QString::fromStdString(film->getSequel()));
    //film_content.setAttribute("Inspiration",QString::fromStdString(film->getInspiration()));
    film_content.setAttribute("Subgenre",QString::number(film->getSubgenre()));

    document.appendChild(film_content);
};
void xmlVisitor::toXml(Serie *serie){
    QDomDocument document;
    QDomElement serie_content=document.createElement("Serie");
    serie_content.setAttribute("Title",QString::fromStdString(serie->getTitle()));
    serie_content.setAttribute("Description",QString::fromStdString(serie->getDescription()));
    serie_content.setAttribute("Starred",QString::number(serie->getStarred()));
    serie_content.setAttribute("Watched",QString::number(serie->getWatched()));
    serie_content.setAttribute("Year",QString::number(serie->getYear()));
    serie_content.setAttribute("Image",QString::fromStdString(serie->getImage()));
    serie_content.setAttribute("Creator",QString::fromStdString(serie->getCreator()));
    serie_content.setAttribute("Producer",QString::fromStdString(serie->getProducer()));
    serie_content.setAttribute("Platform",QString::fromStdString(serie->getPlatforms()));
    serie_content.setAttribute("Duration",QString::number(serie->getDuration()));
    serie_content.setAttribute("Seasons",QString::number(serie->getSeasons()));
    serie_content.setAttribute("Episodes",QString::number(serie->getEpisodes()));
    serie_content.setAttribute("Finished",QString::number(serie->getFinished()));
    //!CERCARE METODO DA POINTER A STRINGA O QPOINTER

     //serie_content.setAttribute("Inspiration",QString::fromStdString(serie->getInspiration()));
    serie_content.setAttribute("Subgenre",QString::number(serie->getSubgenre()));
};
void xmlVisitor::toXml(VideoGame *videogame){
    QDomDocument document;
    QDomElement videogame_content=document.createElement("VideoGame");
    videogame_content.setAttribute("Title",QString::fromStdString(videogame->getTitle()));
    videogame_content.setAttribute("Description",QString::fromStdString(videogame->getDescription()));
    videogame_content.setAttribute("Starred",QString::number(videogame->getStarred()));
    videogame_content.setAttribute("Watched",QString::number(videogame->getWatched()));
    videogame_content.setAttribute("Year",QString::number(videogame->getYear()));
    videogame_content.setAttribute("Image",QString::fromStdString(videogame->getImage()));
    videogame_content.setAttribute("Producer",QString::fromStdString(videogame->getProducer()));
    videogame_content.setAttribute("Platform",QString::fromStdString(videogame->getPlatforms()));
    videogame_content.setAttribute("GameEngine",QString::fromStdString(videogame->getGameEngine()));
    videogame_content.setAttribute("ExpectedHours",QString::number(videogame->getExpectedHours()));
    //!CERCARE METODO DA POINTER A STRINGA O QPOINTER
    //videogame_content.setAttribute("Inspiration",QString::fromStdString(videogame->getInspiration()));
    videogame_content.setAttribute("Subgenre",QString::number(videogame->getSubgenre()));
    document.appendChild(videogame_content);
};