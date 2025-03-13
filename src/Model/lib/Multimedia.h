#ifndef MULTI_H
#define MULTI_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Content.h"

//Genaral Abstract Class for all MULTIMEDIA types of the Library (implemented: Video(Film & Series), Videogames)
class Multimedia : public Content {
    
    private:
        string producer;
        string language;
        QList <string> platforms;
        
    
    public:
        Multimedia(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _language, QList <string> _platforms, Content* _inspiration=NULL);
        
        string getProducer();
        string getLanguage();
        QList <string> getPlatforms();
        
        void setProducer(string producer);
        void setLanguage(string language);
        void setPlatforms(QList <string> platforms);
        virtual ~Multimedia() =0;
        virtual void accept(Visitor* visitor) override = 0;
        virtual void toXml(xmlVisitor* xvisitor) = 0;
};

#endif