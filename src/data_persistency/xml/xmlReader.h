#ifndef XREADER_H
#define XREADER_H
#include "../IReader.h"
#include <memory>
using std::unique_ptr;
using std::make_unique;

class Content;
class Paper;
class Multimedia;
class Video;
class Book;
class Comic;
class Film;
class Serie;
class VideoGame;
class ScienceFiction_Library;

class xmlReader: public IReader{
    private:
        void commonReader(Content* content, QXmlStreamReader& object) const;
        void paperReader(Paper* content, QXmlStreamReader& object) const;
        void multimediaReader(Multimedia* content, QXmlStreamReader& object) const;
        void videoReader(Video* content, QXmlStreamReader& object) const;
        unique_ptr<Book> readBook(QXmlStreamReader& object) const;
        unique_ptr<Comic> readComic(QXmlStreamReader& object) const;
        unique_ptr<Film> readFilm(QXmlStreamReader& object) const;
        unique_ptr<Serie> readSerie(QXmlStreamReader& object) const;
        unique_ptr<VideoGame> readVideoGame(QXmlStreamReader& object) const;
    //
    public:
    ScienceFiction_Library* read(const string& filepath)override;
};

#endif