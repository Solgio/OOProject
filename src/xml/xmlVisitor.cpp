#include <QtCore>
#include <QtXml>
#include <QDebug>
#include "xmlVisitor.h"

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
    film_content.setAttribute("Scriptwriter",QString::fromStdString(film->getScriptwriter()));
    film_content.setAttribute("Duration",QString::number(film->getDuration()));
    //!CERCARE METODO DA POINTER A STRINGA O QPOINTER
    //film_content.setAttribute("Inspiration",QString::fromStdString(comic->getInspiration()));

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
};
void xmlVisitor::toXml(VideoGame *videogame){
    //TODO
};