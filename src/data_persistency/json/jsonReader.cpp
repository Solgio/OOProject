#include "jsonReader.h"
#include "../../Model/lib/Book.h"
#include "../../Model/lib/Comic.h"
#include "../../Model/lib/Film.h"
#include "../../Model/lib/Serie.h"
#include "../../Model/lib/VideoGame.h"

ScienceFiction_Library* jsonReader::read(const string& filepath){
    
    QFile jsonFile(QString::fromStdString(filepath));
    QString jsonString;
    if(jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        jsonString = jsonFile.readAll();
        jsonFile.close(); //chiudo il file dopo averlo letto
    }else{
        qWarning() << "Failed to open file for writing";
        //throw Exception;
    }

    QJsonDocument json_doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray jsonArr = json_doc.array();

    //testing su Qt

    
}