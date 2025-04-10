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
       
    public:
        Film();
        Film(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _director, 
            const string& _producer, const string& _platforms, const string& photoDirector, const unsigned int& _duration, unsigned int _inspiration=0, unsigned int  _prequel=0, unsigned int 
        sequel=0);
        
      
        string getDirector() const;
        string getPhotoDirector()  const;
    
        void setDirector(string_view director);
        void setPhotoDirector(string_view producer);
        
        void accept(Visitor* visitor) override;
        void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ) override;
        void toJson(VisitorJson* vistitorJson) override;
};

#endif