

#ifndef JVESOURCERESOURCESTRUCT_H
#define JVESOURCERESOURCESTRUCT_H


#include <QString>


#include "../definitions/jveFsCheckStatus.h"


struct jveSourceResourceStruct
{
    QString absolutePath;
    int     status;

    // empty constructor
    jveSourceResourceStruct(void) :

        absolutePath ( /*  empty string  */ ),
        status       ( jveFsCheckStatus::Ok )

    {
    }

    // default constructor
    jveSourceResourceStruct(const QString &absolutePath, const int status) :

        absolutePath ( absolutePath ),
        status       ( status       )

    {
    }

    // copy constructor
    jveSourceResourceStruct(const jveSourceResourceStruct &other) :

        absolutePath ( other.absolutePath ),
        status       ( other.status       )

    {
    }
};


#endif // JVESOURCERESOURCESTRUCT_H


