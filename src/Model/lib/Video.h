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
        unsigned int prequel=0;
        unsigned int sequel=0;

    public:
        Video();
        Video(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _platforms, unsigned int _duration, unsigned int _inspiration=0, unsigned int  _prequel=0, unsigned int _sequel=0);
        
        unsigned int getDuration() const;
        unsigned int getPrequel() const;
        unsigned int getSequel() const;
        
        void setDuration(const unsigned int& _duration);
        void setPrequel(const unsigned int& _prequel);
        void setSequel(const unsigned int& _sequel);
        virtual ~Video(){
            unsigned int tp=prequel;
            prequel=sequel;
            sequel=tp;
        };
        virtual void accept(Visitor* visitor) override =0;
        virtual void toXml(xmlVisitor* xvisitor) =0;
        virtual void toJson(VisitorJson* vistitorJson) =0;
};

#endif