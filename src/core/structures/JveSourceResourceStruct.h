

#ifndef JVESOURCERESOURCESTRUCT_H
#define JVESOURCERESOURCESTRUCT_H


#include <QString>


#include "../definitions/JveFsCheckStatus.h"


struct JveSourceResourceStruct
{
    QString absolutePath;
    int     status;

    // empty constructor
    JveSourceResourceStruct(void) :

        absolutePath ( /*  empty string  */ ),
        status       ( JveFsCheckStatus::Ok )

    {
    }

    // default constructor
    JveSourceResourceStruct(const QString &absolutePath, const int status) :

        absolutePath ( absolutePath ),
        status       ( status       )

    {
    }

    // copy constructor
    JveSourceResourceStruct(const JveSourceResourceStruct &other) :

        absolutePath ( other.absolutePath ),
        status       ( other.status       )

    {
    }
};


#endif // JVESOURCERESOURCESTRUCT_H


