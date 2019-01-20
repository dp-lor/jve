

#ifndef JVESOURCERESOURCESTRUCT_H
#define JVESOURCERESOURCESTRUCT_H


#include <QString>


#include "../definitions/JveFsCheckStatus.h"
#include "../definitions/JveFsFileFormat.h"


struct JveSourceResourceStruct
{
    QString absolutePath;
    int     status;
    int     format;

    // empty constructor
    JveSourceResourceStruct(void) :

        absolutePath ( /*  empty string  */         ),
        status       ( JveFsCheckStatus::Ok         ),
        format       ( JveFsFileFormat::Unsupported )

    {
    }

    // default constructor
    JveSourceResourceStruct(const QString &absolutePath, const int status) :

        absolutePath ( absolutePath                 ),
        status       ( status                       ),
        format       ( JveFsFileFormat::Unsupported )

    {
    }

    // copy constructor
    JveSourceResourceStruct(const JveSourceResourceStruct &other) :

        absolutePath ( other.absolutePath ),
        status       ( other.status       ),
        format       ( other.format       )

    {
    }
};


#endif // JVESOURCERESOURCESTRUCT_H


