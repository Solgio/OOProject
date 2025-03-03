#ifndef FILM_H
#define FILM_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Video.h"

class Film : public Video {
   private:
        QString director;
        QString photoDirector;
        QString scriptwriter;
        unsigned int duration; //in minutes
       
      
    public:
        Film(QString _title, QString _subGenre, QString _description, bool _starred, bool _watched, unsigned int _year, QString _director, 
            QString _producer, QString _scriptwriter, unsigned int _duration, QString _language, QString _country, Content* _inspiration=NULL, 
            Film* _prequel=NULL, Film* _sequel=NULL);
            
        QString getDirector();
        QString getProducer();
        QString getScriptwriter();
        unsigned int getDuration();
    
        void setDirector(QString director);
        void setProducer(QString producer);
        void setScriptwriter(QString scriptwriter);
        void setDuration(unsigned int duration);
        void setPrequel(Film* prequel);
        void setSequel(Film* sequel);
        ~Film();
};

#endif