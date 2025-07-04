#include <memory>
#include "./lib/ScienceFictionLibrary.h"
#include "../data_persistency/IReader.h"
#include "../data_persistency/xml/xmlVisitor.h" // Ensure xmlWriter is included
#include "../data_persistency/json/visitorJson.h"
#include "../data_persistency/xml/xmlReader.h" // Ensure xmlReader is included
#include "../data_persistency/json/jsonReader.h"
#include "lib/Video.h"

using std::unique_ptr, std::make_unique;

ScienceFiction_Library::ScienceFiction_Library():contentList(){}

void ScienceFiction_Library::incrementId(){
    newId++;
};
unsigned int ScienceFiction_Library::getNewId()const{
    return newId;
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

void ScienceFiction_Library::clearLibrary(){
    contentList.clear();
};

bool ScienceFiction_Library::saveToFile(const string& filepath)const{
    string extension=filepath.substr(filepath.find_last_of('.'));
    if(extension==".xml"){
        QDomDocument doc;
        QDomProcessingInstruction header = doc.createProcessingInstruction(
            "xml", R"(version="1.0" encoding="UTF-8")");
        doc.appendChild(header);
    
        QDomElement root = doc.createElement("ScienceFictionLibrary");
        doc.appendChild(root);

        xmlVisitor visitor;
    
        // Save all contents
        for (const auto& content : contentList) {
            content->toXml(&visitor, doc, root);
        }
        
        // Save to file with proper error handling
        QFile file(QString::fromStdString(filepath));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Failed to open file for writing:" << file.errorString();
            return false;
        }
        
        QTextStream stream(&file);
        stream.setEncoding(QStringConverter::Utf8);
        doc.save(stream, 4);  // 4 spaces for indentation
        file.close();
        
        return true;
    }
    else if(extension==".json"){
        auto visitor = make_unique<VisitorJson>(QString::fromStdString(filepath));
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
    if(!sequelPrequelControll()){
        throw IncorrectPrequelSequelLoading();
    }
    return true;
}

bool ScienceFiction_Library::sequelPrequelControll(){
    for(auto it = contentList.begin()->get(); it != contentList.end()->get(); it++){
        if(auto q = dynamic_cast<Video*>(it); q && (!q->controllPrequel() || !q->controllSequel())){
            return false;
        }
    }
    return true;
}
