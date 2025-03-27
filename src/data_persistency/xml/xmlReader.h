#ifndef XREADER_H
#define XREADER_H
#include "../IReader.h"
class xmlReader: public IReader{
    private:
        Content* readBook(const QDomElement& object) const;
        Content* readComic(const QDomElement& object) const;
        Content* readFilm(const QDomElement& object) const;
        Content* readSerie(const QDomElement& object) const;
        Content* readVideoGame(const QDomElement& object) const;
    public:
        
        xmlReader(/* args */);
        ~xmlReader();
};

#endif