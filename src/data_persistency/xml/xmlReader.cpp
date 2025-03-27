#include <QtCore>
#include <QtXml>
#include <QDebug>

//? https://www.youtube.com/watch?v=NzQwJdcdRKE

QDomDocument document;

void ListElements(QDomElement root, QString tagname){
    QDomNodeList items = root.elementsByTagName(tagname);
    for(int i = 0; i < items.count(); i++){
        QDomNode item = items.at(i);
        if(item.isElement()){ 
            QDomElement element = item.toElement();
            qDebug() << element.tagName() << " : " << element.text();
        }
    }
}
/*
int main() {
    QFile file("SOMETHING.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Failed to open file for writing";
        return -1;
    }
    else{
        if(document.setContent(&file)){
            qDebug() << "Failed to load document";
            return -1;
        }
        file.close();
    }

    QDomElement root = document.firstChildElement();



    qDebug() << "Finished";
    return 0;
}
 */