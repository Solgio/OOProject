#ifndef SERIES_H
#define SERIES_H
#include <QCoreApplication>
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
        Serie(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
            const string& _platforms, const unsigned int& _duration, const unsigned int& _seasons, const unsigned int& _episodes, const string& _creator, const bool& _finished, unsigned int _inspiration=0, unsigned int _prequel=0,
            unsigned int _sequel=0);
        
      
        unsigned int getSeasons() const;
        unsigned int getEpisodes() const;
        string getCreator() const;
        bool getFinished() const;


        void setSeasons(const unsigned int& seasons);
        void setEpisodes(const unsigned int& episodes);
        void setCreator(string_view creator);
        void setFinished(const bool& finished);

        AttributeDisplayWindow* accept(Visitor* visitor) override;
        CommonEditWindow* acceptEdit(Visitor* visitor) override;
        void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ) override;
        void toJson(VisitorJson* vistitorJson) override;
        string getType() const override;
        virtual ~Serie() = default;
};

#endif
