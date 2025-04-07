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
        Multimedia(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _platforms, unsigned int _inspiration=0);
        
        string getProducer() const;
        string getPlatforms() const;
        
        void setProducer(const string& producer);
        void setPlatforms(const string& platforms);
        virtual ~Multimedia() =0;
        virtual void accept(Visitor* visitor) override = 0;
        virtual void toXml(xmlVisitor* xvisitor) = 0;
        virtual void toJson(VisitorJson* vistitorJson) = 0;
};

#endif