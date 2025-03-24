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
        Video *prequel=NULL;
        Video *sequel=NULL;

    public:
        Video(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _platforms, unsigned int duration, Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL);
        
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
        }
        virtual void accept(Visitor* visitor) override;
        virtual void toXml(xmlVisitor* xvisitor);
        virtual void toJson(VisitorJson* vistitorJson);
};

#endif