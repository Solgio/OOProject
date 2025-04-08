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
        Comic(string _title, unsigned int  _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _author, 
            string _publisher, unsigned int _pages, unsigned int _volume, string _illustrator, string _serie, bool _finished, string _mainCharacter, 
            unsigned int _inspiration=0);
        
        string getType() const;
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