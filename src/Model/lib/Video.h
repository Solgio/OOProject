#ifndef VIDEO_H
#define VIDEO_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Multimedia.h"

//Genaral Abstract Class for all Video types of the Library (implemented: Film, Series)
class Video : public Multimedia {
    private:
        unsigned int quality[2]; //Quality of the video (pixels), il primo valore e' la x e il secondo e' la y
        string country;       //Country of origin
        Video *prequel=NULL;
        Video *sequel=NULL;

    public:
        Video(string _title, bool _subGenre[20], string _description, bool _starred, bool _watched, unsigned int _year, string _image, string _producer, 
            string _language, QList <string> _platforms, string _country, Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL, unsigned int quality[2]);
        
        string getQuality();
        string getCountry();
        Video* getPrequel();
        Video* getSequel();
        
        void setQuality(unsigned int quality[]);
        void setCountry(string _country);
        void setPrequel(Video* _prequel);
        void setSequel(Video* _sequel);
        virtual ~Video(){
            prequel->setSequel(sequel);
            sequel->setPrequel(prequel);
            delete this;
        }
};

#endif