#ifndef BOOK_H
#define BOOK_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Paper.h"

class Book : public Paper {
    Book(string _title, string _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _author, 
        string _publisher, unsigned int _pages, unsigned int _volume, Content* _inspiration=NULL);
};

#endif