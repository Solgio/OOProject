#ifndef IREADER_H
#define IREADER_H
#include <QtXml>
#include <QJsonObject>

class ScienceFiction_Library;

class IReader{
    public:
    virtual ~IReader() {};
    virtual ScienceFiction_Library* read(const string& filename) = 0;
};

#endif