#ifndef CONTENT_H
#define CONTENT_H   
#include "../View/Visitor.h"
#include "../View/Visitor.h"
#include "../xml/xmlVisitor.h"
#include <string>

//? NON SO SE è MEGLIO METTERLO QUI O NEL .CPP
#include <QFile> // per accedere/creare file
#include <QDir> // per gestire la directory
#include <QJsonObject>
#include <QJsonDocument>

using std::string;


//Genaral Abstract Class for all content types of the Library
class Content {
    private:
        static const string subGenres[20];  // Static array for Conversion of the subGenre (this is saves the solution of directly saving a 20 elements array of strings) 

        string title;
        bool choosenGen[20];      //array di bool che corrisponde ai sottogeneri scelti
        string description;
        Content* inspiration=NULL;
        bool starred;
        bool watched;
        unsigned int yearOfRelease; //Year of release, always present in all content types (UNlike year of end)
        string image; //Image of the content
   
    public:
        Content(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, Content* _inspiration=NULL);
        
        string getTitle() const;
        string getSubgenre() const;
        bool getSubgenreArray() const;
        string getDescription() const;
        Content* getInspiration() const;
        bool getStarred() const;
        bool getWatched() const;
        unsigned int getYear() const;
        string getImage() const;

        void setTitle(const string& title);
        void setSubgenre(const string& subgenre);
        void setDescription(const string& description);
        void setInspiration(Content* inspiration);
        void setStarred(const bool& starred);
        void setWatched(const bool& watched);
        void setYear(const unsigned int& year);
        void setImage(const string& image);

        void toJSon();

        virtual ~Content() =0;
        virtual void accept(Visitor* visitor) = 0;
        virtual void toXml(xmlVisitor* xvisitor) = 0;

};

#endif