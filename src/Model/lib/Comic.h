#ifndef COMIC_H
#define COMIC_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Book.h"


class Comic : public Book {
   private:
        string illustrator;
        string serie;  
        bool finished;
        
    public:
        Comic();
        Comic(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _author, 
            const string& _publisher, const unsigned int& _pages, const unsigned int& _volume, const string& _illustrator, const string& _serie, bool& _finished, const string& _mainCharacter, 
            unsigned int _inspiration=0);
        
      
        string getIllustrator() const;
        string getSerie() const;
        bool getFinished() const;

        void setIllustrator(const string& illustrator);
        void setSerie(const string& serie);
        void setFinished(const bool& finished);
        virtual void accept(Visitor* visitor) override;
        virtual void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root );
        virtual void toJson(VisitorJson* vistitorJson);
};

#endif