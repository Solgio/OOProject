#ifndef CONTENT_H
#define CONTENT_H   
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
using std::string;
/*struct subGenre{
    const string subGenres[20]={"Fantasy", "Horror", "Mystery", "Thriller", "Romance", "Drama", "Comedy", "Action", "Adventure", "Documentary",
         "Biography","History", "Western", "War", "Crime", "Musical", "Animation", "Family", "Sports", "Superhero"};
};
static subGenre subGen;
*/

//Genaral Abstract Class for all content types of the Library
class Content {
    private:
        static const string subGenres[20];

        string title;
        bool choosenGen[20];      //array di bool che corrisponde ai sottogeneri scelti
        string description;
        Content* inspiration=NULL;
        bool starred;
        bool watched;
        unsigned int yearOfRelease; //Year of release, always present in all content types (UNlike year of end)
   
    public:
        Content(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, Content* _inspiration=NULL);
        
        string getTitle() const;
        string getSubgenre() const;
        string getDescription() const;
        Content* getInspiration() const;
        bool getStarred() const;
        bool getWatched() const;
        unsigned int getYear() const;

        void setTitle(const string& title);
        void setSubgenre(const string& subgenre);
        void setDescription(const string& description);
        void setInspiration(Content* inspiration);
        void setStarred(const bool starred);
        void setWatched(const bool watched);
        void setYear(const unsigned int year);

        virtual ~Content() =0;

};

#endif