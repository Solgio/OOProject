#include "./lib/Content.h"

static const string subGenres[20]={"Fantasy", "Horror", "Mystery", "Thriller", "Romance", "Drama", "Comedy", "Action", "Adventure", "Documentary", "Biography",
    "History", "Western", "War", "Crime", "Musical", "Animation", "Family", "Sports", "Superhero"};
    
Content::Content(string _title, bool _subGenre[], string _description, bool _starred, bool _watched, unsigned int _year, Content* _inspiration=NULL):
        title(_title), description(_description), starred(_starred), watched(_watched), yearOfRelease(_year), inspiration(_inspiration){
            for(int i=0; i<20; i++){
                choosenGen[i]=_subGenre[i];
            }
        };

string Content::getTitle() const{
            return title;
};

string Content::getSubgenre() const{
    for(int i=0; i<20; i++){
        if(choosenGen[i])
            return subGenres[i];
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