#include "./lib/Video.h"

Video::Video(string _title, string _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _producer, 
            string _language, QList <string> _platforms, string _country, Content* _inspiration=NULL, Video* _prequel=NULL, Video* _sequel=NULL):
            Multimedia(_title, _subGenre, _description, _starred, _watched, _year, _producer, 
            _language, _platforms, _inspiration),
            {

            }