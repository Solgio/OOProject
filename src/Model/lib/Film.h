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
        Film(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _director, 
            string _producer, string _platforms, string photoDirector, unsigned int _duration, unsigned int _inspiration, unsigned int  _prequel=-1, unsigned int 
 sequel=-1);
        
        string getType() const;
        string getDirector() const;
        string getPhotoDirector()  const;
    
        void setDirector(const string& director);
        void setPhotoDirector(const string& producer);
        
        //~Film();
        virtual void accept(Visitor* visitor) override;
        virtual void toXml(xmlVisitor* xvisitor);
        virtual void toJson(VisitorJson* vistitorJson);
        virtual void printContent() const;
};

#endif