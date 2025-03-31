#ifndef JSONREADER_H
#define JSONREADER_H
#include "../IReader.h"
class jsonReader: public IReader{
    private:/*
        Book* readBook(QXmlStreamReader& object) const;
        Comic* readComic(QXmlStreamReader& object) const;
        Film* readFilm(QXmlStreamReader& object) const;
        Serie* readSerie(QXmlStreamReader& object) const;
        VideoGame* readVideoGame(QXmlStreamReader& object) const;*/
    //
    public:
        ScienceFiction_Library* read(const string& filepath);
};

#endif