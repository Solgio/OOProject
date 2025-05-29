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
       
        AttributeDisplayWindow* accept(Visitor* visitor) override = 0;
        void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ) override= 0;
        void toJson(VisitorJson* vistitorJson) override= 0;
        string getType() const override= 0;
};

#endif
