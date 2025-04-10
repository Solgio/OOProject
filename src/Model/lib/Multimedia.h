#ifndef MULTI_H
#define MULTI_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Content.h"

//Genaral Abstract Class for all MULTIMEDIA types of the Library (implemented: Video(Film & Serie), Videogames)
class Multimedia : public Content {
    
    private:
        string producer;
        string platforms;        
    
    public:
        Multimedia();
        Multimedia(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
            const string& _platforms, unsigned int _inspiration=0);
        
        string getProducer() const;
        string getPlatforms() const;
        
        void setProducer(string_view producer);
        void setPlatforms(string_view platforms);
       
        virtual void accept(Visitor* visitor) override = 0;
        virtual void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ) = 0;
        virtual void toJson(VisitorJson* vistitorJson) = 0;
};

#endif