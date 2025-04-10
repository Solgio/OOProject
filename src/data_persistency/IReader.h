#ifndef IREADER_H
#define IREADER_H
#include <QtXml>
#include <QJsonObject>
#include <string>
using std::string;

class ScienceFiction_Library;

class IReader{
    public:
    virtual ~IReader()=default;
    virtual ScienceFiction_Library* read(const string& filename) = 0;
};

#endif