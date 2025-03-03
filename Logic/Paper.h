#ifndef PAPER_H
#define PAPER_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Content.h"

//Genaral Abstract Class for all Paper types of the Library (implemented: Book, Comic)
class Paper : public Content {
    private:
        QString author;
        QString publisher;
        unsigned int pages;
        unsigned int volume;    
            
    public:
        Paper(QString _title, QString _subGenre, QString _description, bool _starred, bool _watched, unsigned int _year, QString _author, 
            QString _publisher, unsigned int _pages, unsigned int _volume, Content* _inspiration=NULL);
        
        QString getAuthor();
        QString getPublisher();
        unsigned int getPages();
        unsigned int getVolume();
        
        void setAuthor(QString author);
        void setPublisher(QString publisher);
        void setPages(unsigned int pages);
        void setVolume(unsigned int volume);
        virtual ~Paper() =0;
};

#endif