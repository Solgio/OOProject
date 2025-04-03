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
        Paper(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _author, 
            string _publisher, unsigned int _pages, unsigned int _volume, unsigned int _inspiration=0);
        
        string getAuthor() const;
        string getPublisher() const;
        unsigned int getPages() const;
        unsigned int getVolume() const;
        
        void setAuthor(const string& author);
        void setPublisher(const string& publisher);
        void setPages(const unsigned int& pages);
        void setVolume(const unsigned int& volume);
        virtual ~Paper() =0;
        virtual void accept(Visitor* visitor) override = 0;
        virtual void toXml(xmlVisitor* xvisitor) = 0;
        virtual void toJson(VisitorJson* vistitorJson) = 0;
};

#endif