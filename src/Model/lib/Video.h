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
        Video *prequel=nullptr;
        Video *sequel=nullptr;

    public:
        Video(string _title, Subgenre _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _platforms, unsigned int duration, Content* _inspiration=nullptr, Video* _prequel=nullptr, Video* _sequel=nullptr);
        
        unsigned int & getDuration();
        Video* getPrequel();
        Video* getSequel();
        
        void setDuration(unsigned int quality);
        void setPrequel(Video* _prequel);
        void setSequel(Video* _sequel);
        virtual ~Video(){
            prequel->setSequel(sequel);
            sequel->setPrequel(prequel);
            delete this;
        };
        virtual void accept(Visitor* visitor) override =0;
        virtual void toXml(xmlVisitor* xvisitor) =0;
        virtual void toJson(VisitorJson* vistitorJson) =0;
};

#endif