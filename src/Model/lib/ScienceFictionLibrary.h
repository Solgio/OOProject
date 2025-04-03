#ifndef LIBRARY_H
#define LIBRARY_H
#include "Content.h"
#include <vector>
using std::vector;

class ScienceFiction_Library{
    private:
        unsigned int newId;
        ScienceFiction_Library* instance;
        vector<Content*> contentList;
        vector<Content*> shownContentList;
        ScienceFiction_Library();   //Singleton

    public:
        void incrementId();
        unsigned int getNewId();
        void testPrint()const;
        Content* searchId(const unsigned int& __id_t);
        void addContent(Content* content);
        void removeContent(Content* content);
        vector<Content*> getContentList();
        void showAllContent();            //Shows all the content in the library
        void filterContent(const string& _title);
        void filterContent(const unsigned int& _year);
        void filterContent(Subgenre genre);
        void watchedOrNot(const bool& _watched);         //Shows only the watched or not watched content
        void starredOrNot(const bool& _starred);         //Shows only the starred or not starred content
        void clearLibrary();                //Clear the library
        void clearShown();
        
        static ScienceFiction_Library& getInstance(){
            static ScienceFiction_Library instance;
            return instance;
        }

        // Delete so it is impossible to copy the singleton
        ScienceFiction_Library(const ScienceFiction_Library&) = delete;
        ScienceFiction_Library& operator=(const ScienceFiction_Library&) = delete;
        // The only possible instance of the ScienceFIction_Library is the one created with the getInstance() method and 
        //it can't be copied nor canceled before the end of the programm
};
#endif