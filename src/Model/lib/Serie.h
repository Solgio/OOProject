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
        Serie();
        Serie(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _platforms, unsigned int duration, unsigned int _seasons, unsigned int _episodes, string _creator, bool _finished, unsigned int _inspiration, unsigned int _prequel=0,
            unsigned int _sequel=0);
        
        string getType() const;
        unsigned int getSeasons();
        unsigned int getEpisodes();
        string getCreator();
        bool getFinished();


        void setSeasons(unsigned int seasons);
        void setEpisodes(unsigned int episodes);
        void setCreator(string creator);
        void setFinished(bool finished);

        //~Serie();
        virtual void accept(Visitor* visitor) override;
        virtual void toXml(xmlVisitor* xvisitor);
        virtual void toJson(VisitorJson* vistitorJson);
        virtual void printContent() const;
};

#endif