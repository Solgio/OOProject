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
            return it.get();
        }

    }
    return nullptr;
};

void ScienceFiction_Library::addContent(Content* content){
    contentList.push_back(unique_ptr<Content>(content));
    incrementId();
};

void ScienceFiction_Library::removeContent(const Content* content){
    for(auto it = contentList.begin(); it != contentList.end();){
        if((*it)->getInspiration() == content->getId()){  // If the content that we want to remove is an inspiration for another content,
            (*it)->setInspiration(0);         // we set the inspiration to 0
            ++it;
        }
        else if ((*it)->getId() == content->getId()) {  // Compare by ID instead
            it = contentList.erase(it);
        } else {
            ++it;
        }
    }
};

const vector<unique_ptr<Content>>& ScienceFiction_Library::getContentList()const{
    return contentList;
};

void ScienceFiction_Library::showAllContent(){
    shownContentList.clear();
    for(const auto& it : contentList){
        shownContentList.push_back(it.get());
    }
    testPrint();
};

void ScienceFiction_Library::filterContent(string_view _title){
    shownContentList.clear();
    for(const auto& it : contentList){
        if(it->getTitle() == _title){
            shownContentList.push_back(it.get());
        }
    }
};

void ScienceFiction_Library::filterContent(const unsigned int& _year){
    shownContentList.clear();
    for(const auto& it : contentList){
        if(it->getYear() == _year){
            shownContentList.push_back(it.get());
        }
    }
};

void ScienceFiction_Library::filterContent(const Subgenre& genre){
    shownContentList.clear();
    for (const auto& it : contentList) {
        if (it->hasAnySubgenre(genre)) {
            shownContentList.push_back(it.get());
        }
    }
};

//! ALTERNATIVA, DA VALUTARE CON QT COSA CONVIENE. PROBABILMENTE QUESTA E' PIU' UTILE
void ScienceFiction_Library::filteredListbyGen(const unsigned int& genre){
    shownContentList.clear();
    for(const auto& it : contentList){
        if(it->hasAnySubgenre(static_cast<Subgenre>(genre))){
            shownContentList.push_back(it.get());
        }
    }
};

void ScienceFiction_Library::watchedOrNot(const bool& _watched){
    shownContentList.clear();
    if(_watched){
        for(const auto& it : contentList){
            if(it->getWatched()){
                shownContentList.push_back(it.get());
            }
        }
    }
    else{
        for(const auto& it : contentList){
            if(!it->getWatched()){
                shownContentList.push_back(it.get());
            }
        }
    }
};
void ScienceFiction_Library::starredOrNot(const bool& _starred){
    shownContentList.clear();
    if(_starred){
        for(const auto& it : contentList){
            if(it->getStarred()){
                shownContentList.push_back(it.get());
            }
        }
    }
    else{
        for(const auto& it : contentList){
            if(!it->getStarred()){
                shownContentList.push_back(it.get());
            }
        }
    }
};

void ScienceFiction_Library::clearLibrary(){
    shownContentList.clear();
    contentList.clear();
};
void ScienceFiction_Library::clearShown(){
    shownContentList.clear();
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
        unique_ptr<VisitorJson> visitor = make_unique<VisitorJson>(QString::fromStdString(filepath));
        for(const auto& it : contentList){
            it->toJson(visitor.get());
        }
        return true;
    }
    return true;
}
    

bool ScienceFiction_Library::loadFromFile(const string& filepath){
    clearLibrary();
    std::unique_ptr<IReader> reader;
    string extension=filepath.substr(filepath.find_last_of('.'));
    if(extension==".xml"){
        qDebug() << "XML" ;
        reader=make_unique<xmlReader>();
    }
    else if(extension==".json"){
        qDebug() << "JSON" ;
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