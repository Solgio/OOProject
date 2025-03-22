#ifndef VISITOR_JSON_H
#define VISITOR_JSON_H


#include <QFile> // per accedere/creare file
#include <QDir> // per gestire la directory
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Book;
class Comic;
class Serie;
class Film;
class VideoGame;

class VisitorJson{
    private:

        QString fileName("libreriaJson.json");
        QDir dir("Json/"); // indirizzamento relativo a partire da "." , 
        // dir() è di default "."

        // We create the directory if needed
        if(!dir.exists()){ dir.mkpath(dir.dirName());} //Partendo dalla cartella ".", se ./JFile/ NON esiste, creamo la cartella

        QFile libreria(dir + fileName);
    public:

        void setDirectory(QString directory) = 0;
        void setFileName(QString fileName) = 0;
        virtual void toFileJson(Book *book) = 0;
        virtual void toFileJson(Comic *comic) = 0;
        virtual void toFileJson(Film *movie) = 0;
        virtual void toFileJson(Serie *serie) = 0;
        virtual void toFileJson(VideoGame *videogame) = 0;
};
#endif