#include "./lib/Book.h"

Book::Book(string _title, string _subGenre, string _description, bool _starred, bool _watched, unsigned int _year, string _author, 
    string _publisher, unsigned int _pages, unsigned int _volume, Content* _inspiration=NULL):
    Paper(_title, _subGenre, _description, _starred, _watched, _year, _author, _publisher, _pages, _volume, _inspiration){};