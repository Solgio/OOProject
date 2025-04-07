#ifndef IREADER_H
#define IREADER_H
#include <QtXml>
#include <QJsonObject>
#include "../Model/lib/Content.h"
#include "../Model/lib/ScienceFictionLibrary.h"

class IReader{
    public:
    virtual ~IReader() {};
    virtual ScienceFiction_Library* read(const string& filename) = 0;
};

#endif