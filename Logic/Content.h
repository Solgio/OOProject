#ifndef CONTENT_H
#define CONTENT_H   
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>

//Genaral Abstract Class for all content types of the Library
class Content {
    private:
        QString title;
        QString subGenre;
        QString description;
        Content* inspiration=NULL;
        bool starred;
        bool watched;
        unsigned int yearOfRelease; //Year of release, always present in all content types (UNlike year of end)
   
    public:
        Content(QString _title, QString _subGenre, QString _description, bool _starred, bool _watched, unsigned int _year, Content* _inspiration=NULL);
        
        QString getTitle();
        QString getSubgenre();
        QString getDescription();
        Content* getInspiration();
        bool getStarred();
        bool getWatched();
        unsigned int getYear();

        void setTitle(QString title);
        void setSubgenre(QString subgenre);
        void setDescription(QString description);
        void setInspiration(Content* inspiration);
        void setStarred(bool starred);
        void setWatched(bool watched);
        void setYear(unsigned int year);

        virtual ~Content() =0;

};

#endif