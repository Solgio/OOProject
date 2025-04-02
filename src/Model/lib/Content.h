#ifndef CONTENT_H
#define CONTENT_H   
#include "../../View/Visitor.h"
#include "../../data_persistency/json/visitorJson.h"
#include "../../data_persistency/xml/xmlVisitor.h"
#include <string>
using std::string;

enum class Subgenre {
    NONE = 0,
    ACTION = 1 << 0,
    COMEDY = 1 << 1,
    DRAMA = 1 << 2,
    HORROR = 1 << 3,
    ROMANCE = 1 << 4,
    THRILLER = 1 << 4,
    MYSTERY = 1 << 5,
    ADVENTURE = 1 << 6,
    WESTERN = 1 << 7,
    WAR = 1 << 8,
    MUSICAL = 1 << 9,
    FAMILY = 1 << 10,
    SPORTS = 1 << 11,
    SUPERHERO = 1 << 12
};

//Genaral Abstract Class for all content types of the Library
class Content {
    private:
        unsigned int id; //ID of the content, unique for each content
        string title;
        Subgenre subgenres; //Bitmasks for the Subgenres
        string description;
        bool starred;
        bool watched;
        unsigned int yearOfRelease; //Year of release, always present in all content types (UNlike year of end)
        string image; //Image of the content
        unsigned int inspiration; //Inspiration for the content
        
    public:
        
        Content(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, unsigned int _inspiration=0);
        string getType() const;
        string getTitle() const;
        int getSubgenre() const;
        bool hasSubgenre(Subgenre genre) const;
        bool hasAnySubgenre(Subgenre genres) const;
        string getSubgenreString() const;
        string getDescription() const;
        unsigned int getInspiration() const;
        bool getStarred() const;
        bool getWatched() const;
        unsigned int getYear() const;
        string getImage() const;

        void setTitle(const string& title);
        void addSubgenre(const int& genre);
        void setDescription(const string& description);
        void setInspiration(unsigned int inspiration);
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