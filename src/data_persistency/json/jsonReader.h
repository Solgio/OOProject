#ifndef JSONREADER_H
#define JSONREADER_H
#include "../IReader.h"
#include "../Model/lib/ScienceFictionLibrary.h"

class jsonReader: public IReader{
    private:
        Book* readBook(const QJsonObject& object) const;
        Comic* readComic(const QJsonObject& object) const;
        Film* readFilm(const QJsonObject& object) const;
        Serie* readSerie(const QJsonObject& object) const;
        VideoGame* readVideogame(const QJsonObject& object) const;
    public:
        ScienceFiction_Library* read(const string& filepath);
};

#endif