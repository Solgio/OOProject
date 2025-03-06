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
            break;
        }
    }
}

vector<Content*>& filterContent(string filter);