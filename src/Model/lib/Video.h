#ifndef VIDEO_H
#define VIDEO_H
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "Multimedia.h"

//Genaral Abstract Class for all Video types of the Library (implemented: Film, Series)
class Video : public Multimedia {
    private:
        unsigned int quality[1][1]; //Quality of the video (pixels)
        string country;       //Country of origin
        Video *prequel=NULL;
        Video *sequel=NULL;

    public:
        Video(string _title, string _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _producer, 
            string _language, string _country, Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL);
        
        unsigned int getQuality();
        string getCountry();
        Video* getPrequel();
        Video* getSequel();
        
        void setQuality(unsigned int quality);
        void setCountry(string country);
        void setPrequel(Video* prequel);
        void setSequel(Video* sequel);
        virtual ~Video() =0;
};

#endif