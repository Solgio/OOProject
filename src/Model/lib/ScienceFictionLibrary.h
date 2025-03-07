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
        vector<Content*>& filterContent(bool& _watched);
        vector<Content*>& filterContent(unsigned int& _year);
        vector<Content*>& filterContent(bool choosenGen[20]);
        ~ScienceFiction_Library();
};
#endif