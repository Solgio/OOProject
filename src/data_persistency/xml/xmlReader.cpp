#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <vector>
#include "xmlReader.h"
#include "../../Model/lib/ScienceFictionLibrary.h"
#include "../../Model/lib/Content.h"
#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"
using std::vector, std::string;

//? https://www.youtube.com/watch?v=JTG65RiDbEQ


Book* xmlReader::readBook(const QXmlStreamReader& object) const{

}
Comic* xmlReader::readComic(const QXmlStreamReader& object) const{

}
Film* xmlReader::readFilm(const QXmlStreamReader& object) const{

}
Serie* xmlReader::readSerie(const QXmlStreamReader& object) const{

}
VideoGame* xmlReader::readVideoGame(const QXmlStreamReader& object) const{

}



bool xmlReader::fromXml(const string filepath){
    
    QFile file(QString::fromStdString(filepath));

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "Failed to open file for writing";
        //! Forse qui è meglio un'eccezione   
        file.close();
        return false;       
    }

    // Clear the library before loading new data
    //getInstance().clearLibrary();
    
    QXmlStreamReader xmlreader(&file);
    while (!xmlreader.atEnd() && !xmlreader.hasError()) {
        QXmlStreamReader::TokenType token = xmlreader.readNext();
        /*
        if (token == QXmlStreamReader::StartElement) {
            if (xmlreader.name() == "Book") {
                contentList.addContent(readBook(xmlreader));
            }
            else if (xmlreader.name() == "Comic") {
                contentList.addContent(readComic(xmlreader));
            }
            else if (xmlreader.name() == "Film") {
                contentList.addContent(readFilm(xmlreader));
            }
            else if (xmlreader.name() == "Serie") {
                contentList.addContent(readSerie(xmlreader));
            }
            else if (xmlreader.name() == "VideoGame") {
                contentList.addContent(readVideoGame(xmlreader));
            }
            else if (xmlreader.name() == "Content") {
                // Handle generic content if needed
            }
            else {
                xmlreader.raiseError(QObject::tr("Not a valid content type"));
            }
        }
    }*/

    if (xmlreader.hasError()) {
        qWarning() << "XML error:" << xmlreader.errorString();
        //clearLibrary();
        return false;
    }

    file.close();
    return true;
 }