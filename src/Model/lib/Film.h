#ifndef FILM_H
#define FILM_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Video.h"

class Film : public Video {
   private:
        string director;
        string photoDirector;
        string scriptwriter;
        unsigned int duration; //in minutes
       
    public:
        Film(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _director, 
            string _producer, string _scriptwriter, unsigned int _duration, string _language, string _country, Content* _inspiration=NULL, 
            Film* _prequel=NULL, Film* _sequel=NULL);
            
        string getDirector() const;
        string getPhotoDirector()  const;
        string getScriptwriter() const;
        unsigned int getDuration() const;
    
        void setDirector(const string& director);
        void setPhotoDirector(const string& producer);
        void setScriptwriter(const string& scriptwriter);
        void setDuration(const unsigned int& duration);
        
        ~Film();
        virtual void accept(Visitor* visitor) override;
        virtual void toXml(xmlVisitor* xvisitor);
};

#endif