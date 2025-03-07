#include "./lib/ScienceFictionLibrary.h"

ScienceFiction_Library::ScienceFiction_Library():contentList(){}

void ScienceFiction_Library::addContent(Content* content){
    contentList.push_back(content);
}

void ScienceFiction_Library::removeContent(Content* content){
    for(vector<Content*>::iterator it = contentList.begin(); it != contentList.end(); it++){

        if((*it)->getInspiration() == content){     //If the content that we want to remove is an inspiration for another content,
            (*it)->setInspiration(NULL);            //we set the inspiration to NULL
        }
        if(*it == content){
            contentList.erase(it);
        }
    }
}

vector<Content*>& ScienceFiction_Library::filterContent(string& _title){
    vector<Content*> filteredListbyTitle;
    for(vector<Content*>::iterator it = contentList.begin(); it != contentList.end(); it++){
        if((*it)->getTitle() == _title){
            filteredListbyTitle.push_back(*it);
        }
    }
};
vector<Content*>& ScienceFiction_Library::filterContent(bool choosenGen[20]){
    vector<Content*> filteredListbyGen;
    for(vector<Content*>::iterator it = contentList.begin(); it != contentList.end(); it++){
        for(int i=0; i<20; i++){
            if(choosenGen[i] && *((*it)->getSubgenreArray()+i)){
                filteredListbyGen.push_back(*it);
            }
        }
    }
};

vector<Content*>& ScienceFiction_Library::filterContent(unsigned int& _year){
    vector<Content*> filteredListbyYear;
    for(vector<Content*>::iterator it = contentList.begin(); it != contentList.end(); it++){
        if((*it)->getYear() == _year){
            filteredListbyYear.push_back(*it);
        }
    }
};
vector<Content*>& filterContent();
