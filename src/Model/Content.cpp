#include "lib/Content.h"
#include "lib/ScienceFictionLibrary.h"
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
    
Content::Content(string& _title, unsigned int& _subGenre, string& _description, bool& _starred, bool& _watched, unsigned int& _year, string& _image, unsigned int _inspiration):
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
bool Content::hasAnySubgenre(Subgenre genres) const {
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
void Content::setTitle(const string& ntitle){
    title=ntitle;
};
void Content::addSubgenre(const int& genre) {
    subgenres = static_cast<Subgenre>(static_cast<underlying_type_t<Subgenre>>(subgenres) | genre);
}
void Content::setDescription(const string& ndescription){
    description=ndescription;
};
void Content::setInspiration(unsigned int ninspiration){
    inspiration=ninspiration;
};
void Content::setStarred(const bool& nstarred){
    starred=nstarred;
    //(!starred)? starred=true : starred=false;
};
void Content::setWatched(const bool& nwatched){
    watched=nwatched;
    //(!watched)? watched=true : watched=false;
};
void Content::setYear(const unsigned int& nyear){
    yearOfRelease=nyear;
};
void Content::setImage(const string& nimage){
    image=nimage;
};