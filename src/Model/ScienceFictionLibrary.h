#ifndef LIBRARY_H
#define LIBRARY_H
#include <QCoreApplication>
#include "./lib/Content.h"

class ScienceFiction_Library{
    private:
        QList<Content*> contentList;
    public:
        void addContent(Content* content);
        void removeContent(Content* content);
        QList<Content*> getContentList();
        QList<Content*>& filterContent(string filter);
        ~ScienceFiction_Library();
};
#endif