

#ifndef JVESOURCESITEMSTRUCT_H
#define JVESOURCESITEMSTRUCT_H


#include <QString>


#include "../definitions/jveSourcesItemType.h"
#include "../definitions/jveSourcesItemStatus.h"


typedef struct _jveSourcesItemStruct
{
    QString id;
    int     type;
    int     status;
    QString absolutePath;
    QString name;
    QString baseName;
} jveSourcesItemStruct;


#endif // JVESOURCESITEMSTRUCT_H


