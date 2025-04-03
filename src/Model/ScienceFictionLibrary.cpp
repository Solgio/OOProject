#include "./lib/ScienceFictionLibrary.h"

ScienceFiction_Library::ScienceFiction_Library():contentList(){}

void ScienceFiction_Library::incrementId(){
    newId++;
}
unsigned int ScienceFiction_Library::getNewId(){
    return newId;
}


void ScienceFiction_Library::testPrint(const ScienceFiction_Library* library) const{
    for(auto it = contentList.begin(); it != contentList.end();){
        //(*it)->printContent();
    }
};

Content* ScienceFiction_Library::searchId(const unsigned int& id){
    for(const auto& it : contentList){
        if(id==it->getId()){
            return it;
        }
    }
}

void ScienceFiction_Library::addContent(Content* content){
    contentList.push_back(content);
    incrementId();
}

void ScienceFiction_Library::removeContent(Content* content){
    for(auto it = contentList.begin(); it != contentList.end();){
        if((*it)->getInspiration() == content->getId()){  //If the content that we want to remove is an inspiration for another content,
            (*it)->setInspiration(0);         //we set the inspiration to nullptr
            ++it;
        }
        if (*it == content) {
            it = contentList.erase(it);
        } else {
            ++it;
        }
    }
}

vector<Content*> ScienceFiction_Library::getContentList(){
    return contentList;
};

void ScienceFiction_Library::showAllContent(){
    for(const auto& it : contentList){
        shownContentList.push_back(it);
    }
    
};

void ScienceFiction_Library::filterContent(const string& _title){
    for(const auto& it : contentList){
        if(it->getTitle() == _title){
            shownContentList.push_back(it);
        }
    }
};

void ScienceFiction_Library::filterContent(const unsigned int& _year){
    for(const auto& it : contentList){
        if(it->getYear() == _year){
            shownContentList.push_back(it);
        }
    }
};

void ScienceFiction_Library::filterContent(Subgenre genre){
    vector<Content*> result;
    for (const auto& it : contentList) {
        if (it->hasAnySubgenre(genre)) {
            shownContentList.push_back(it);
        }
    }
};

//VERSIONE ALTERNATIVA: Invece che un array viene passato un singolo indice per verificare in O(1) o un array di indici ma nel caso peggiore la coomplessità è la stessa
/*vector<Content*>& ScienceFiction_Library::filterGen(unsigned int index){
    vector<Content*> filteredListbyGen;
    for(const auto& it : contentList){
        if(choosenGen[index]){
            filteredListbyGen.push_back(it);
        }
        
    }
};*/

void ScienceFiction_Library::watchedOrNot(const bool& _watched){
    if(_watched){
        for(const auto& it : contentList){
            if(it->getWatched()){
                shownContentList.push_back(it);
            }
        }
    }
    else{
        for(const auto& it : contentList){
            if(!it->getWatched()){
                shownContentList.push_back(it);
            }
        }
    }
};
void ScienceFiction_Library::starredOrNot(const bool& _starred){
    if(_starred){
        for(const auto& it : contentList){
            if(it->getStarred()){
                shownContentList.push_back(it);
            }
        }
    }
    else{
        for(const auto& it : contentList){
            if(!it->getStarred()){
                shownContentList.push_back(it);
            }
        }
    }
};

void ScienceFiction_Library::clearLibrary(){
    for(auto& it : contentList){
        delete it;
    }
    contentList.clear();
}