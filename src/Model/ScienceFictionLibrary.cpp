#include "./lib/ScienceFictionLibrary.h"

ScienceFiction_Library::ScienceFiction_Library():contentList(){}

void ScienceFiction_Library::addContent(Content* content){
    contentList.push_back(content);
}

void ScienceFiction_Library::removeContent(Content* content){
    for(auto it = contentList.begin(); it != contentList.end();){
        if((*it)->getInspiration() == content){  //If the content that we want to remove is an inspiration for another content,
            (*it)->setInspiration(NULL);         //we set the inspiration to NULL
            ++it;
        }
        if (*it == content) {
            it = contentList.erase(it);
        } else {
            ++it;
        }
    }
}

vector<Content*>& ScienceFiction_Library::filterContent(string& _title){
    vector<Content*> filteredListbyTitle;
    for(const auto& it : contentList){
        if(it->getTitle() == _title){
            filteredListbyTitle.push_back(it);
        }
    }
};

vector<Content*>& ScienceFiction_Library::filterContent(unsigned int& _year){
    vector<Content*> filteredListbyYear;
    for(const auto& it : contentList){
        if(it->getYear() == _year){
            filteredListbyYear.push_back(it);
        }
    }
};

vector<Content*>& ScienceFiction_Library::filterContent(bool choosenGen[20]){
    vector<Content*> filteredListbyGen;
    for(const auto& it : contentList){
        for(int i=0; i<20; i++){
            if(choosenGen[i] && it->getSubgenreArray()+i){
                filteredListbyGen.push_back(it);
            }
        }
    }
};

/*VERSIONE ALTERNATIVA: Invece che un array viene passato un singolo indice per verificare in O(1) o un array di indici ma nel caso peggiore la coomplessità è la stessa
vector<Content*>& ScienceFiction_Library::filterGen(unsigned int index){
    vector<Content*> filteredListbyGen;
    for(const auto& it : contentList){
        if(choosenGen[index]){
            filteredListbyGen.push_back(it);
        }
        
    }
};*/

vector<Content*>& ScienceFiction_Library::watchedOrNot(bool& _watched){
    if(_watched){
        vector<Content*> watchedList;
        for(const auto& it : contentList){
            if(it->getWatched()){
                watchedList.push_back(it);
            }
        }
    }
    else{
        vector<Content*> notWatchedList;
        for(const auto& it : contentList){
            if(!it->getWatched()){
                notWatchedList.push_back(it);
            }
        }
    }
};
vector<Content*>& ScienceFiction_Library::starredOrNot(bool& _starred){
    if(_starred){
        vector<Content*> watchedList;
        for(const auto& it : contentList){
            if(it->getStarred()){
                watchedList.push_back(it);
            }
        }
    }
    else{
        vector<Content*> notWatchedList;
        for(const auto& it : contentList){
            if(!it->getStarred()){
                notWatchedList.push_back(it);
            }
        }
    }
};