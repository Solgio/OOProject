#ifndef SERIES_H
#define SERIES_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Video.h"

class Serie : public Video {
    private:
        unsigned int seasons;
        unsigned int episodes;
        string creator;
        bool finished;

    public:
        Serie(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _platforms, unsigned int duration, unsigned int _seasons, unsigned int _episodes, string _creator, bool _finished, Content* _inspiration=NULL, Video* _prequel=NULL,
            Video* _sequel=NULL);
        
        unsigned int getSeasons();
        unsigned int getEpisodes();
        string getCreator();
        bool getFinished();
        unsigned int getYearOfEnd();

        void setSeasons(unsigned int seasons);
        void setEpisodes(unsigned int episodes);
        void setCreator(string creator);
        void setFinished(bool finished);
        void setYearOfEnd(unsigned int yearOfEnd);
        ~Serie();
        virtual void accept(Visitor* visitor) override;
        virtual void toXml(xmlVisitor* xvisitor);
};

#endif