#ifndef LIBRARY_H
#define LIBRARY_H
#include <QCoreApplication>
#include "Content.h"
#include <vector>
using std::vector;

class ScienceFiction_Library{
    private:
        std::vector<Content*> contentList;

    public:
        void addContent(Content* content);
        void removeContent(Content* content);
        vector<Content*> getContentList();
        vector<Content*>& filterContent(string filter);
        ~ScienceFiction_Library();
};
#endif