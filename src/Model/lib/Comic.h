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
            const string& _publisher, const unsigned int& _pages, const unsigned int& _volume, const string& _illustrator, const string& _serie, const bool& _finished, const string& _mainCharacter, 
            unsigned int _inspiration=0);
        
      
        string getIllustrator() const;
        string getSerie() const;
        bool getFinished() const;

        void setIllustrator(string_view illustrator);
        void setSerie(string_view serie);
        void setFinished(const bool& finished);

        AttributeDisplayWindow* accept(Visitor* visitor) override;
        CommonEditWindow* acceptEdit(Visitor* visitor) override;
        void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ) override;
        void toJson(VisitorJson* vistitorJson) override;
        string getType() const override;

        virtual ~Comic()  = default; 
};

#endif
