#ifndef LIBRARY_H
#define LIBRARY_H
#include "Content.h"
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;

class ScienceFiction_Library{
    private:
        unsigned int newId;
        ScienceFiction_Library* instance;
        vector<unique_ptr<Content>> contentList;
        vector<unique_ptr<Content>> shownContentList;
        ScienceFiction_Library();   //Singleton

    public:
        void incrementId();
        unsigned int getNewId()const;
        void testPrint()const;
        Content* searchId(const unsigned int& __id_t);
        void addContent(Content* content);
        void removeContent(Content* content);
        vector<Content*> getContentList()const;
        void showAllContent();            //Shows all the content in the library
        void filterContent(const string& _title);
        void filterContent(const unsigned int& _year);
        void filterContent(Subgenre genre);
        void filteredListbyGen(unsigned int& genre);
        void watchedOrNot(const bool& _watched);         //Shows only the watched or not watched content
        void starredOrNot(const bool& _starred);         //Shows only the starred or not starred content
        void clearLibrary();                //Clear the library
        void clearShown();
        
        static ScienceFiction_Library& getInstance(){
            static ScienceFiction_Library instance;
            return instance;
        }

        bool saveToFile(const string& filepath)const; //Saves the library to a file
        bool loadFromFile(const string& filepath); //Loads the library from a file
        // Delete so it is impossible to copy the singleton
        ScienceFiction_Library(const ScienceFiction_Library&) = delete;
        ScienceFiction_Library& operator=(const ScienceFiction_Library&) = delete;
        // The only possible instance of the ScienceFIction_Library is the one created with the getInstance() method and 
        //it can't be copied nor canceled before the end of the programm
};
#endif