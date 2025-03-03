#ifndef COMIC_H
#define COMIC_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Book.h"


class Comic : public Book {
   private:
        QString illustrator;
        QString series;
        bool finished;
        unsigned int yearOfEnd;
    public:
        Comic(QString _title, QString _subGenre, QString _description, bool _starred, bool _watched, unsigned int _year, QString _author, 
            QString _publisher, unsigned int _pages, unsigned int _volume, QString _illustrator, QString _series, bool _finished, Content* _inspiration=NULL);
        
        QString getIllustrator();
        QString getSeries();
        bool getFinished();

        void setIllustrator(QString illustrator);
        void setSeries(QString series);
        void setFinished(bool finished);
        ~Comic();
};

#endif