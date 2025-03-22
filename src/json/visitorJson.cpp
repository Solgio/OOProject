#include "visitorJson.h"

#include "../Model/lib/Book.h"
#include "../Model/lib/Comic.h"
#include "../Model/lib/Film.h"
#include "../Model/lib/Serie.h"
#include "../Model/lib/VideoGame.h"

void VisitorJson::toFileJson(Book *book){

    libreria.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto
    QJsonObject oggettoJSon;

    oggettoJSon.insert("Title", book->getTitle());
    oggettoJSon.insert("Genres", choosenGen); //! non ho la minima idea se fuziona o no
    oggettoJSon.insert("Description", description);
    oggettoJSon.insert("Year of Release", yearOfRelease);
    oggettoJSon.insert("Image", image); // contiene la image path
    oggettoJSon.insert("Inspiration", inspiration->getTitle()); // Contiene il titolo dell'inspirazione
};
void VisitorJson::toFileJson(Comic *comic){
    printf("Comic visited\n");
};
void VisitorJson::toFileJson(Film *movie){
    printf("Film visited\n");
};
void VisitorJson::toFileJson(Serie *serie){
    printf("Serie visited\n");
};
void VisitorJson::toFileJson(VideoGame *videogame){
    printf("VideoGame visited\n");
};  