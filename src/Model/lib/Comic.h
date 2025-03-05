#ifndef COMIC_H
#define COMIC_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Book.h"


class Comic : public Book {
   private:
        string illustrator;
        string series;  
        bool finished;
        
    public:
        Comic(string _title, bool _subGenre[], string _description, bool _starred, bool _watched, unsigned int _year, string _author, 
            string _publisher, unsigned int _pages, unsigned int _volume, string _illustrator, string _series, bool _finished, string _mainCharacter, 
            Content* _inspiration=NULL);
        
        string getIllustrator() const;
        string getSeries() const;
        bool getFinished() const;

        void setIllustrator(const string& illustrator);
        void setSeries(const string& series);
        void setFinished(const bool& finished);
        ~Comic();
};

#endif