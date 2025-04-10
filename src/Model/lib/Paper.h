#ifndef PAPER_H
#define PAPER_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Content.h"

//Genaral Abstract Class for all Paper types of the Library (implemented: Book, Comic)
class Paper : public Content {
    private:
        string author;
        string publisher;
        unsigned int pages;
        unsigned int volume;    
            
    public:
        Paper();
        Paper(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _author, 
            const string& _publisher, const unsigned int& _pages, const unsigned int& _volume, unsigned int _inspiration=0);
        
        string getAuthor() const;
        string getPublisher() const;
        unsigned int getPages() const;
        unsigned int getVolume() const;
        
        void setAuthor(string_view author);
        void setPublisher(string_view publisher);
        void setPages(const unsigned int& pages);
        void setVolume(const unsigned int& volume);
       
        virtual void accept(Visitor* visitor) override = 0;
        virtual void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ) = 0;
        virtual void toJson(VisitorJson* vistitorJson) = 0;
};

#endif