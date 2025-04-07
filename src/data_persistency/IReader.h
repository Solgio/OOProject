#ifndef IREADER_H
#define IREADER_H
#include <QtXml>
#include <QJsonObject>
#include "../Model/lib/Content.h"
#include "../Model/lib/ScienceFictionLibrary.h"

class IReader{
    public:
    virtual ~IReader() {};
    //! senti antonio se anche lui userà string e controllerà se per caso fa il controllo del init
    virtual ScienceFiction_Library* read(const QJsonObject& object) = 0;
    virtual ScienceFiction_Library* read(string& filename) = 0;
};

#endif