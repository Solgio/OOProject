#ifndef JSONREADER_H
#define JSONREADER_H
#include "../IReader.h"
#include "../../Model/lib/ScienceFictionLibrary.h"

class jsonReader: public IReader{
    private:
        Book* readBook(const QJsonObject& object) const;
        Comic* readComic(const QJsonObject& object) const;
        Film* readFilm(const QJsonObject& object) const;
        Serie* readSerie(const QJsonObject& object) const;
        VideoGame* readVideogame(const QJsonObject& object) const;

        void readContent(Content* content, const QJsonObject& object);
        void readPaper(Paper* paper, const QJsonObject& object);
        void readMultimedia(Multimedia* mult, const QJsonObject& object);
        void readVideo(Video* video, const QJsonObject& object);
    public:
        ScienceFiction_Library* read(const string& filepath);
};

#endif