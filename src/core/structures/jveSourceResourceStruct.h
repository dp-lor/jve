

#ifndef JVESOURCERESOURCESTRUCT_H
#define JVESOURCERESOURCESTRUCT_H


#include <QString>


#include "../definitions/jveFsCheckStatus.h"


typedef struct _jveSourceResourceStruct
{
    QString absolutePath;
    int     status;
} jveSourceResourceStruct;


#endif // JVESOURCERESOURCESTRUCT_H


