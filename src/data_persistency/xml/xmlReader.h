#ifndef XREADER_H
#define XREADER_H
#include "../IReader.h"
class xmlReader: public IReader{
    private:
        Book* readBook(const QXmlStreamReader& object) const;
        Comic* readComic(const QXmlStreamReader& object) const;
        Film* readFilm(const QXmlStreamReader& object) const;
        Serie* readSerie(const QXmlStreamReader& object) const;
        VideoGame* readVideoGame(const QXmlStreamReader& object) const;
    public:
        bool fromXml(const string filepath);
};

#endif