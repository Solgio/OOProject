#ifndef LIBRARY_H
#define LIBRARY_H
#include <QCoreApplication>
#include "Content.h"
#include <vector>
using std::vector;

class ScienceFiction_Library{
    private:
        vector<Content*> contentList;

    public:
        void addContent(Content* content);
        void removeContent(Content* content);
        vector<Content*> getContentList();
        vector<Content*>& filterContent(string& _title);
        vector<Content*>& filterContent(unsigned int& _year);
        vector<Content*>& filterContent(bool choosenGen[20]);
        vector<Content*>& filterContent();
        vector<Content*>& watchedOrNot(bool& _watched);         //Shows only the watched or not watched content
        vector<Content*>& starredOrNot(bool& _starred);         //Shows only the starred or not starred content
        ~ScienceFiction_Library();
};
#endif