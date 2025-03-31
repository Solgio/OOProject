#ifndef XREADER_H
#define XREADER_H
#include "../IReader.h"
class xmlReader: public IReader{
    private:
        void commonReader(Content* content, QXmlStreamReader& object) const;
        void paperReader(Paper* content, QXmlStreamReader& object) const;
        void multimediaReader(Multimedia* content, QXmlStreamReader& object) const;
        void videoReader(Video* content, QXmlStreamReader& object) const;
        Book* readBook(QXmlStreamReader& object) const;
        Comic* readComic(QXmlStreamReader& object) const;
        Film* readFilm(QXmlStreamReader& object) const;
        Serie* readSerie(QXmlStreamReader& object) const;
        VideoGame* readVideoGame(QXmlStreamReader& object) const;
    //
    public:
    ScienceFiction_Library* read(const string& filepath);
};

#endif