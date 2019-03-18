#ifndef JEXPORT_H
#define JEXPORT_H

#include "qlist.h"
#include "qstring.h"

///@brief Version of JSON Validating
#define VERSION = RFC4627


//! <ID,VALUE>
template<class A, class B>
class JObject
{
    private:
    QString str_item;
    int int_item;

public:
    void Set(A valueA, B valueB)
    {
        int_item = valueA;
        str_item = valueB;
    }

};

//! JExporter a JSON Exporter tool
class JExport
{


public:
    JExport();



};

#endif // JEXPORT_H
