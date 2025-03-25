#include <QtCore>
#include <QtXml>
#include <QDebug>

//? https://www.youtube.com/watch?v=NzQwJdcdRKE

QDomDocument document;

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
 