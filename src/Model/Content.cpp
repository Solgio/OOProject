#include "lib/Content.h"
#include "lib/Book.h"
#include "lib/Comic.h"
#include "lib/Film.h"
#include "lib/Serie.h"
#include "lib/VideoGame.h"
#include "lib/ScienceFictionLibrary.h"
#include <iostream>

using std::underlying_type_t;   //I would use to_underlying but  it is C++23 so I will use this

inline   Subgenre operator|(Subgenre a, Subgenre b) {
    return static_cast<Subgenre>(static_cast<underlying_type_t<Subgenre>>(a) | static_cast<underlying_type_t<Subgenre>>(b));
}
inline Subgenre operator&(Subgenre a, Subgenre b) {
    return static_cast<Subgenre>(static_cast<underlying_type_t<Subgenre>>(a) & static_cast<underlying_type_t<Subgenre>>(b));
}

Content::Content():
        title(), subgenres(), description(), starred(), watched(), yearOfRelease(), image(), inspiration(0) { 
            id = ScienceFiction_Library::getInstance().getNewId()+1;
        };
    
Content::Content(const string& _title, const unsigned int& _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, unsigned int _inspiration):
        title(_title),subgenres(static_cast<Subgenre>(_subGenre)), description(_description), starred(_starred), watched(_watched), yearOfRelease(_year),image(_image), inspiration(_inspiration) { 
            id = ScienceFiction_Library::getInstance().getNewId()+1; //Get the new ID from the library
        };

unsigned int Content::getId() const{
    return id;
};        
string Content::getTitle() const{
    return title;
};

int Content::getSubgenre() const{
    return static_cast<underlying_type_t<Subgenre>>(subgenres);
};
// Check if content has any of the subgenres
bool Content::hasAnySubgenre(const Subgenre genres) const {
    return static_cast<underlying_type_t<Subgenre>>(subgenres & genres) != 0;
}
// Check if content has a specific subgenre
bool Content::hasSubgenre(const Subgenre genre) const {
    return (subgenres & genre) == genre;
}
string Content::getSubgenreString() const{
    string result;
    if (subgenres == Subgenre::NONE) return "None";
    if (hasSubgenre(Subgenre::ACTION)) result += "Action, ";
    if (hasSubgenre(Subgenre::COMEDY)) result += "Comedy, ";
    if (hasSubgenre(Subgenre::DRAMA)) result += "Drama, ";
    if (hasSubgenre(Subgenre::HORROR)) result += "Horror, ";
    if (hasSubgenre(Subgenre::ROMANCE)) result += "Romance, ";
    if (hasSubgenre(Subgenre::THRILLER)) result += "Thriller, ";
    if (hasSubgenre(Subgenre::MYSTERY)) result += "Mystery, ";
    if (hasSubgenre(Subgenre::ADVENTURE)) result += "Adventure, ";
    if (hasSubgenre(Subgenre::WESTERN)) result += "Western, ";
    if (hasSubgenre(Subgenre::WAR)) result += "War, ";
    if (hasSubgenre(Subgenre::MUSICAL)) result += "Musical, ";
    if (hasSubgenre(Subgenre::FAMILY)) result += "Family, ";
    if (hasSubgenre(Subgenre::SPORTS)) result += "Sports, ";
    if (hasSubgenre(Subgenre::SUPERHERO)) result += "Superhero, ";
    // Remove trailing comma and space
    if (!result.empty()) {
        result.erase(result.size() - 2);
    }
    return result;
};
string Content::getDescription() const{
            return description;
};
unsigned int Content::getInspiration() const{
            return inspiration;
};
bool Content::getStarred() const{
            return starred;
};
bool Content::getWatched() const{
            return watched;
};
unsigned int Content::getYear() const{
            return yearOfRelease;
};
string Content::getImage() const{
            return image;
};

void Content::setId(const unsigned int& nid){
    id=nid;
};
void Content::setTitle(string_view ntitle){
    title=ntitle;
};
void Content::addSubgenre(const unsigned int& genre) {
    subgenres = static_cast<Subgenre>(static_cast<underlying_type_t<Subgenre>>(subgenres) | genre);
}
void Content::setSubgenre(const unsigned int& nsubgenre){
    subgenres=static_cast<Subgenre>(nsubgenre);
};
void Content::setDescription(string_view ndescription){
    description=ndescription;
};
void Content::setInspiration(const unsigned int ninspiration){
    inspiration=ninspiration;
};
void Content::setStarred(const bool& nstarred){
    starred=nstarred;
};
void Content::setWatched(const bool& nwatched){
    watched=nwatched;
};
void Content::setYear(const unsigned int& nyear){
    yearOfRelease=nyear;
};
void Content::setImage(string_view nimage){
    image=nimage;
};