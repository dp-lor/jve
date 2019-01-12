

#ifndef JVESOURCESITEMSTRUCT_H
#define JVESOURCESITEMSTRUCT_H


#include <QString>


#include "../definitions/jveSourcesItemType.h"
#include "../definitions/jveSourcesItemStatus.h"


typedef struct _jveSourcesItemStruct
{
    int     type;
    int     status;
    QString id;
    QString absolutePath;
    QString displayName;
    QString searchHaystack;
} jveSourcesItemStruct;


#endif // JVESOURCESITEMSTRUCT_H


