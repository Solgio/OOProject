#ifndef MULTI_H
#define MULTI_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Content.h"

//Genaral Abstract Class for all MULTIMEDIA types of the Library (implemented: Video(Film & Series), Videogames)
class Multimedia : public Content {
    
    private:
        QString producer;
        QString language;
        vector <QString> platforms;
        virtual ~Multimedia() =0;
};

#endif