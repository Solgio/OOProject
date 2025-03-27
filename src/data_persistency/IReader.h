#ifndef IREADER_H
#define IREADER_H
#include <QtXml>
#include <QJsonObject>
#include "../Model/lib/Content.h"

class IReader{
    public:
    virtual ~IReader() {};
    virtual Content* read(const QJsonObject& object) = 0;
    virtual Content* read(QDomElement& element) = 0;
};

#endif