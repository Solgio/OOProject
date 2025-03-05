#ifndef BOOK_H
#define BOOK_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Paper.h"

class Book : public Paper {
    private:
        string mainCharacter;

    public:

    Book(string _title, bool _subGenre[], string _description, bool _starred, bool _watched, unsigned int _year, string _author, 
        string _publisher, unsigned int _pages, unsigned int _volume, string _mainCharacter, Content* _inspiration=NULL);

        string getMainCharacter() const;
        void setMainCharacter(const string& mainCharacter);
        ~Book();
    };

#endif


// Books in this context is to be considered as a class for all NARRATIVE books, given the nature of the library (Sci-fi only).