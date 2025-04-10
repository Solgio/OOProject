#ifndef BOOK_H
#define BOOK_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Paper.h"

class Book : public Paper {
    private:
        string mainCharacter;

    public:
        Book();
        Book(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _author, 
            const string& _publisher, const unsigned int& _pages, const unsigned int& _volume, const string& _mainCharacter, unsigned int _inspiration=0);

      
        string getMainCharacter() const;
        void setMainCharacter(string_view mainCharacter);

        void accept(Visitor* visitor) override;
        void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root) override;
        void toJson(VisitorJson* vistitorJson) override;
    };

#endif


// Books in this context is to be considered as a class for all NARRATIVE books, given the nature of the library (Sci-fi only).