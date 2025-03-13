#ifndef LIBRARY_H
#define LIBRARY_H
#include <QCoreApplication>
#include "Content.h"
#include <vector>
using std::vector;

class ScienceFiction_Library{
    private:
        vector<Content*> contentList;
        ScienceFiction_Library();   //Singleton

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
        
        ScienceFiction_Library& getInstance(){
            static ScienceFiction_Library instance;
            return instance;
        }

        // Delete so it is impossible to copy the singleton
        ScienceFiction_Library(const ScienceFiction_Library&) = delete;
        ScienceFiction_Library& operator=(const ScienceFiction_Library&) = delete;
};
#endif