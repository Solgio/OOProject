#include "./lib/Content.h"

static const string subGenres[20]={"Fantasy", "Horror", "Mystery", "Thriller", "Romance", "Drama", "Comedy", "Action", "Adventure", "Documentary", "Biography",
    "History", "Western", "War", "Crime", "Musical", "Animation", "Family", "Sports", "Superhero"};
    
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
string Content::getSubgenre() const{
    for(int i=0; i<20; i++){
        if(choosenGen[i])
            return subGenres[i];
    }
};
bool Content::getSubgenreArray() const{
    return *choosenGen;
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
void Content::setSubgenre(const string& nsubgenre){
};
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


QJsonObject Content::toJSon(){
    QString path("JFile/"); //
    QDir dir; // Initialize to the desired dir if 'path' is relative
        // By default the program's working directory "." is used.

    // We create the directory if needed
    if (!dir.exists(path)){ //Partendo da questa cartella, se ./JFile/ NON esiste, creamo la cartella
        dir.mkpath(path);
    }
    
    QFile LibraryFile(path + "Library.json"); //SE IL FILE NON ESISTE crea uno nuovo, altrimenti apre il file
    LibraryFile.open(QIODevice::ReadWrite); // o QFile::WriteOnly per scrivere soltanto

    QJsonObject oggettoJSon;

    oggettoJSon.insert("Title", title);
    oggettoJSon.insert("Genres", choosenGen); //! non ho la minima idea se fuziona o no
    oggettoJSon.insert("Description", description);
    oggettoJSon.insert("Year of Release", yearOfRelease);
    oggettoJSon.insert("Image", image); // contiene la image path
    oggettoJSon.insert("Inspiration", inspiration->getTitle()); // Contiene il titolo dell'inspirazione

    return oggettoJSon;

};
