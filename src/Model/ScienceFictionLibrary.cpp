#include <memory>
#include "./lib/ScienceFictionLibrary.h"
#include "../data_persistency/IReader.h"
#include "../data_persistency/xml/xmlVisitor.h" // Ensure xmlWriter is included
#include "../data_persistency/json/visitorJson.h"
#include "../data_persistency/xml/xmlReader.h" // Ensure xmlReader is included
#include "../data_persistency/json/jsonReader.h"
using std::unique_ptr;
using std::make_unique;

ScienceFiction_Library::ScienceFiction_Library():contentList(){}

void ScienceFiction_Library::incrementId(){
    newId++;
};
unsigned int ScienceFiction_Library::getNewId()const{
    return newId;
};


void ScienceFiction_Library::testPrint() const{
    /*for(const auto& it : shownContentList){
        it->printContent();
    }*/
};

Content* ScienceFiction_Library::searchId(const unsigned int& id){
    for(const auto& it : contentList){
        if(id==it->getId()){
            return it;
        }

    }
    return nullptr;
};

void ScienceFiction_Library::addContent(Content* content){
    contentList.push_back(content);
    incrementId();
};

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
};

vector<Content*> ScienceFiction_Library::getContentList(){
    return contentList;
};

void ScienceFiction_Library::showAllContent(){
    shownContentList.clear();
    for(const auto& it : contentList){
        shownContentList.push_back(it);
    }
    testPrint();
};

void ScienceFiction_Library::filterContent(const string& _title){
    shownContentList.clear();
    for(const auto& it : contentList){
        if(it->getTitle() == _title){
            shownContentList.push_back(it);
        }
    }
};

void ScienceFiction_Library::filterContent(const unsigned int& _year){
    shownContentList.clear();
    for(const auto& it : contentList){
        if(it->getYear() == _year){
            shownContentList.push_back(it);
        }
    }
};

void ScienceFiction_Library::filterContent(Subgenre genre){
    shownContentList.clear();
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
    shownContentList.clear();
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
    shownContentList.clear();
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
};
void ScienceFiction_Library::clearShown(){
    for(auto& it : shownContentList){
        delete it;
    }
    ;shownContentList.clear();
}

bool ScienceFiction_Library::saveToFile(const string& filepath)const{
    string extension=filepath.substr(filepath.find_last_of('.'));
    if(extension==".xml"){
        QDomDocument doc;
        QDomProcessingInstruction header = doc.createProcessingInstruction(
        "xml", "version=\"1.0\" encoding=\"UTF-8\"");
        doc.appendChild(header);
    
        QDomElement root = doc.createElement("ScienceFictionLibrary");
        doc.appendChild(root);

        xmlVisitor visitor;
    
        //Save all contents
        for (const auto& content : contentList) {
            content->toXml(&visitor, doc, root);
        }
        // Save to file
        QFile file(QString::fromStdString(filepath));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Failed to open file for writing:" << file.errorString();
            return false;
        }
    
        QTextStream stream(&file);
        doc.save(stream, 4);  // 4 spaces for indentation
        file.close();
        
        
    }
    else if(extension==".json"){
        unique_ptr<VisitorJson> visitor;
        for(const auto& it : contentList){
            it->toJson(visitor.get());
        
        return true;
        }
    }
    return true;
}
    

bool ScienceFiction_Library::loadFromFile(const string& filepath){
    clearLibrary();
    std::unique_ptr<IReader> reader;
    string extension=filepath.substr(filepath.find_last_of('.'));
    if(extension==".xml"){
        reader=make_unique<xmlReader>();
    }
    else if(extension==".json"){
        reader=make_unique<jsonReader>();
    }
    else{
        return false;
    }   
    try {
        ScienceFiction_Library* result = reader->read(filepath);
        return (result != nullptr);  // Return true if read was successful
    } 
    catch (const std::exception& e) {
        qCritical() << "Error loading file:" << e.what();
        return false;
    }
}