#ifndef SERIES_H
#define SERIES_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Video.h"

class Series : public Video {
    private:
        unsigned int seasons;
        unsigned int episodes;
        string creator;
        bool finished;
        unsigned int yearOfEnd;

    public:
        Series(string _title, string _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _producer, 
            string _language, string _country, unsigned int _seasons, unsigned int _episodes, string _creator, bool _finished, unsigned int _yearOfEnd, 
            Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL);
        
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
        ~Series();
};

#endif