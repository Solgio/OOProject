#include "lib/Content.h"

inline Subgenre operator|(Subgenre a, Subgenre b) {
    return static_cast<Subgenre>(static_cast<int>(a) | static_cast<int>(b));
}
inline Subgenre operator&(Subgenre a, Subgenre b) {
    return static_cast<Subgenre>(static_cast<int>(a) & static_cast<int>(b));
}
    
Content::Content(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, Content* _inspiration):
        title(_title), subgenres(_subGenre), description(_description), starred(_starred), watched(_watched), yearOfRelease(_year),image(_image), inspiration(_inspiration) {}

string Content::getTitle() const{
            return title;
};

int Content::getSubgenre() const{
            return static_cast<int>(subgenres);
};
// Check if content has any of the subgenres
bool Content::hasAnySubgenre(Subgenre genres) const {
    return static_cast<int>(subgenres & genres) != 0;
}
// Check if content has a specific subgenre
bool Content::hasSubgenre(Subgenre genre) const {
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
Content* Content::getInspiration() const{
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

void Content::setTitle(const string& ntitle){
    title=ntitle;
};
void Content::addSubgenre(const int& genre) {
    subgenres = static_cast<Subgenre>(static_cast<int>(subgenres) | genre);
}
void Content::setDescription(const string& ndescription){
    description=ndescription;
};
void Content::setInspiration(Content* ninspiration){
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

