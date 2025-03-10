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
        Series(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _language, QList <string> _platforms, string _country, unsigned int _seasons, unsigned int _episodes, string _creator, bool _finished, unsigned int _yearOfEnd, 
            Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL, unsigned int quality[2]);
        
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
        virtual void accept(Visitor* visitor) override;
};

#endif