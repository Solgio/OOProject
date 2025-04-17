#ifndef VISITOR_JSON_H
#define VISITOR_JSON_H


#include <QFile> // per accedere/creare file
#include <QDir> // per gestire la directory
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Content;
class Paper;
class Multimedia;
class Video;
class Book;
class Comic;
class Serie;
class Film;
class VideoGame;

class VisitorJson{
private:
    QFile libreria;

public:

    VisitorJson();
    VisitorJson(QString filePath);

    void setDirectory(QString _directory);
    void setFileName(QString _fileName);
    void setLibreria(QString path);

    QDir getDirectory();
    QString getFileName();

    virtual void toFileJson(const Book* book) = 0;
    virtual void toFileJson(const Comic* comic) = 0;
    virtual void toFileJson(const Film* movie) = 0;
    virtual void toFileJson(const Serie* serie) = 0;
    virtual void toFileJson(const VideoGame* videogame) = 0;




void insertContent(const Content* _content, QJsonObject& oggettoJSon);
void insertPaper(const Paper* _paper, QJsonObject& oggettoJSon);
void insertMultimedia(const Multimedia* _multimedia, QJsonObject& oggettoJSon);
void insertVideo(const Video* _video, QJsonObject& oggettoJSon);
};
#endif
