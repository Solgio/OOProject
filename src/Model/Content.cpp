#include "./lib/Content.h"

Content::Content(string _title, subGenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, Content* _inspiration=NULL):
        title(_title), description(_description), starred(_starred), watched(_watched), yearOfRelease(_year), inspiration(_inspiration){
            genMap.insert(std::pair<const string, bool>("Fantasy", _subGenre.subGenres[0]));
            genMap.insert(std::pair<const string, bool>("Horror", _subGenre.subGenres[1]));
            genMap.insert(std::pair<const string, bool>("Mystery", _subGenre.subGenres[2]));
            genMap.insert(std::pair<const string, bool>("Thriller", _subGenre.subGenres[3]));
            genMap.insert(std::pair<const string, bool>("Romance", _subGenre.subGenres[4]));
            genMap.insert(std::pair<const string, bool>("Drama", _subGenre.subGenres[5]));
            genMap.insert(std::pair<const string, bool>("Comedy", _subGenre.subGenres[6]));
            genMap.insert(std::pair<const string, bool>("Action", _subGenre.subGenres[7]));
            genMap.insert(std::pair<const string, bool>("Adventure", _subGenre.subGenres[8]));
            genMap.insert(std::pair<const string, bool>("Documentary", _subGenre.subGenres[9]));
            genMap.insert(std::pair<const string, bool>("Biography", _subGenre.subGenres[10]));
            genMap.insert(std::pair<const string, bool>("History", _subGenre.subGenres[11]));
            genMap.insert(std::pair<const string, bool>("Western", _subGenre.subGenres[12]));
            genMap.insert(std::pair<const string, bool>("War", _subGenre.subGenres[13]));
            genMap.insert(std::pair<const string, bool>("Crime", _subGenre.subGenres[14]));
            genMap.insert(std::pair<const string, bool>("Musical", _subGenre.subGenres[15]));
            genMap.insert(std::pair<const string, bool>("Animation", _subGenre.subGenres[16]));
            genMap.insert(std::pair<const string, bool>("Family", _subGenre.subGenres[17]));
            genMap.insert(std::pair<const string, bool>("Sports", _subGenre.subGenres[18]));
            genMap.insert(std::pair<const string, bool>("Superhero", _subGenre.subGenres[19]));
            genMap.insert(std::pair<const string, bool>("Fanfilm", _subGenre.subGenres[20]);
        };

string Content::getTitle() const{
            return title;
};

string Content::getSubgenre() const{
    const char* getSubName(enum subGenre s) 
    {
       switch (s) 
       {
          case FANTASY: subGenres[0]=true; return "Fantasy";
          case HORROR: subGenres[1]=true; return "Horror";
            case MYSTERY: subGenres[2]=true; return "Mystery";
            case THRILLER: subGenres[3]=true; return "Thriller";
            case ROMANCE: subGenres[4]=true; return "Romance";
            case DRAMA: subGenres[5]=true; return "Drama";
            case COMEDY: subGenres[6]=true; return "Comedy";
            case ACTION: subGenres[7]=true; return "Action";
            case ADVENTURE: subGenres[8]=true; return "Adventure";
            case DOCUMENTARY: subGenres[9]=true; return "Documentary";
            case BIOGRAPHY: subGenres[10]=true; return "Biography";
            case HISTORY: subGenres[11]=true; return "History";
            case WESTERN: subGenres[12]=true; return "Western";
            case WAR: subGenres[13]=true; return "War";
            case CRIME: subGenres[14]=true; return "Crime";
            case MUSICAL: subGenres[15]=true; return "Musical";
            case ANIMATION: subGenres[16]=true; return "Animation";
            case FAMILY: subGenres[17]=true; return "Family";
            case SPORTS: subGenres[18]=true; return "Sports";
            case SUPERHERO: subGenres[19]=true; return "Superhero";
            case FANFILM: subGenres[20]=true; return "Fanfilm";
            default: return "Unknown";
       }
    }
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

void Content::setTitle(const string& ntitle){
    title=ntitle;
};
void Content::setSubgenre(const string& nsubgenre){

};
void Content::setDescription(const string& ndescription){
    description=ndescription;
};
void Content::setInspiration(Content* ninspiration){
    inspiration=ninspiration;
};
void Content::setStarred(const bool nstarred){
    (!starred)? starred=true : starred=false;
};
void Content::setWatched(const bool nwatched){
    (!watched)? watched=true : watched=false;
};
void Content::setYear(const unsigned int nyear){
    yearOfRelease=nyear;
};