#include "./lib/Content.h"

inline Subgenre operator|(Subgenre a, Subgenre b) {
    return static_cast<Subgenre>(static_cast<int>(a) | static_cast<int>(b));
}
    
Content::Content(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, Content* _inspiration=NULL):
        title(_title), description(_description), starred(_starred), watched(_watched), yearOfRelease(_year), inspiration(_inspiration){
            for(int i=0; i<20; i++){
                choosenGen[i]=_subGenre[i]; // ho dei dubbi su questa parte
            }
        };

string Content::getTitle() const{
            return title;
};

//! This function is not implemented in the definitive version of the project
//! TO BE DEFINED
Subgenre Content::getSubgenre() const{
            return subgenres;
};
// Check if content has any of the subgenres
bool Content::hasAnySubgenre(Subgenre genres) const {
    return (subgenres & genres) != 0;
}
// Check if content has a specific subgenre
bool Content::hasSubgenre(Subgenre genre) const {
    return (subgenres & genre) == genre;
}
string Content::getSubgenreString() const{
    string result;
    if (subgenres == NONE) return "None";
    if (hasSubgenre(ACTION)) result += "Action, ";
    if (hasSubgenre(COMEDY)) result += "Comedy, ";
    if (hasSubgenre(DRAMA)) result += "Drama, ";
    if (hasSubgenre(HORROR)) result += "Horror, ";
    if (hasSubgenre(ROMANCE)) result += "Romance, ";
    if (hasSubgenre(THRILLER)) result += "Thriller, ";
    if (hasSubgenre(MYSTERY)) result += "Mystery, ";
    if (hasSubgenre(ADVENTURE)) result += "Adventure, ";
    if (hasSubgenre(WESTERN)) result += "Western, ";
    if (hasSubgenre(WAR)) result += "War, ";
    if (hasSubgenre(MUSICAL)) result += "Musical, ";
    if (hasSubgenre(FAMILY)) result += "Family, ";
    if (hasSubgenre(SPORTS)) result += "Sports, ";
    if (hasSubgenre(SUPERHERO)) result += "Superhero, ";
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
void Content::addSubgenre(Subgenre genre) {
    subgenres = subgenres | genre;
}
void Content::setDescription(const string& ndescription){
    description=ndescription;
};
void Content::setInspiration(Content* ninspiration){
    inspiration=ninspiration;
};
void Content::setStarred(const bool& nstarred){
    (!starred)? starred=true : starred=false;
};
void Content::setWatched(const bool& nwatched){
    (!watched)? watched=true : watched=false;
};
void Content::setYear(const unsigned int& nyear){
    yearOfRelease=nyear;
};
void Content::setImage(const string& nimage){
    image=nimage;
};

