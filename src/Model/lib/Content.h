#ifndef CONTENT_H
#define CONTENT_H   
#include "subgenre.h"
#include "../View/Visitor.h"
#include "../json/visitorJson.h"
#include "../xml/xmlVisitor.h"
#include <string>
using std::string;


//Genaral Abstract Class for all content types of the Library
class Content {
    private:
        string title;
        Subgenre subgenres; //Bitmasks for the Subgenres
        string description;
        bool starred;
        bool watched;
        unsigned int yearOfRelease; //Year of release, always present in all content types (UNlike year of end)
        string image; //Image of the content
        Content* inspiration; //Inspiration for the content7
        
    public:
        Content(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, Content* _inspiration=NULL);
        
        string getTitle() const;
        Subgenre getSubgenre() const;
        bool hasSubgenre(Subgenre genre) const;
        bool hasAnySubgenre(Subgenre genres) const;
        string getSubgenreString() const;
        string getDescription() const;
        Content* getInspiration() const;
        bool getStarred() const;
        bool getWatched() const;
        unsigned int getYear() const;
        string getImage() const;

        void setTitle(const string& title);
        void addSubgenre(Subgenre genre);
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
        virtual void toJson(VisitorJson* vistitorJson) = 0;

};

#endif