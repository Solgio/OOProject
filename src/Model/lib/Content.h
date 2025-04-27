#ifndef CONTENT_H
#define CONTENT_H
#include <QtXml>
#include "../../View/Visitor.h"
#include "../../data_persistency/json/visitorJson.h"
#include "../../data_persistency/xml/xmlVisitor.h"
#include <string>
using std::string;
using std::string_view;

enum class Subgenre
{
    NONE = 0,
    ACTION = 1 << 0,
    COMEDY = 1 << 1,
    DRAMA = 1 << 2,
    HORROR = 1 << 3,
    ROMANCE = 1 << 4,
    THRILLER = 1 << 5,
    MYSTERY = 1 << 6,
    ADVENTURE = 1 << 7,
    WESTERN = 1 << 8,
    WAR = 1 << 9,
    MUSICAL = 1 << 10,
    FAMILY = 1 << 11,
    SPORTS = 1 << 12,
    SUPERHERO = 1 << 13
};

// Genaral Abstract Class for all content types of the Library
class Content
{
private:
    unsigned int id; // ID of the content, unique for each content
    string title;
    Subgenre subgenres; // Bitmasks for the Subgenres
    string description;
    bool starred;
    bool watched;
    unsigned int yearOfRelease; // Year of release, always present in all content types (UNlike year of end)
    string image;               // Image of the content
    unsigned int inspiration;   // Inspiration for the content

public:
    Content();
    Content(const string &_title, const unsigned int &_subGenre, const string &_description, const bool &_starred, const bool &_watched, const unsigned int &_year, const string &_image, unsigned int _inspiration = 0);
    unsigned int getId() const;
    string getTitle() const;
    int getSubgenre() const;
    bool hasSubgenre(const Subgenre genre) const;
    bool hasAnySubgenre(const Subgenre genres) const;
    string getSubgenreString() const;
    string getDescription() const;
    unsigned int getInspiration() const;
    bool getStarred() const;
    bool getWatched() const;
    unsigned int getYear() const;
    string getImage() const;

    void setId(const unsigned int &id);
    void setTitle(string_view title);
    void addSubgenre(const unsigned int &genre);
    void setSubgenre(const unsigned int &subgenre);
    void setDescription(string_view description);
    void setInspiration(const unsigned int inspiration);
    void setStarred(const bool &starred);
    void setWatched(const bool &watched);
    void setYear(const unsigned int &year);
    void setImage(string_view image);

    virtual ~Content()=default;
    virtual void accept(Visitor *visitor)= 0;
    virtual void toXml(xmlVisitor *xvisitor, QDomDocument &doc, QDomElement &root)= 0;
    virtual void toJson(VisitorJson *vistitorJson)= 0;
    virtual string getType() const = 0;
    //virtual bool isTypeOf(const ContentType& type) const = 0;

};

#endif