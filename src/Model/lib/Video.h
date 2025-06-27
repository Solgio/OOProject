#ifndef VIDEO_H
#define VIDEO_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Multimedia.h"

//Genaral Abstract Class for all Video types of the Library (implemented: Film, Serie)
class Video : public Multimedia {
    private:
        unsigned int duration; //in minutes
        unsigned int prequel;
        unsigned int sequel;

    public:
        Video();
        Video(const string& _title, const unsigned int&  _subGenre, const string& _description, const bool& _starred, const bool& _watched, const unsigned int& _year, const string& _image, const string& _producer, 
            const string& _platforms, const unsigned int& _duration, unsigned int _inspiration=0, unsigned int _prequel=0, unsigned int _sequel=0);
        
        unsigned int getDuration() const;
        unsigned int getPrequel() const;
        unsigned int getSequel() const;
        
        void setDuration(const unsigned int& _duration);
        void setPrequel(const unsigned int& _prequel);
        void setSequel(const unsigned int& _sequel);

        bool controllPrequel();
        bool controllSequel();

        virtual ~Video(){
            unsigned int tp=prequel;
            prequel=sequel;
            sequel=tp;
        };

        AttributeDisplayWindow* accept(Visitor* visitor) override =0;
        CommonEditWindow* acceptEdit(Visitor* visitor) override =0;
        void toXml(xmlVisitor* xvisitor, QDomDocument& doc, QDomElement& root ) override=0;
        void toJson(VisitorJson* vistitorJson) override=0;
        string getType() const override=0;
};

#endif
