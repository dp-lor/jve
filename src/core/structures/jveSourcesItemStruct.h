

#ifndef JVESOURCESITEMSTRUCT_H
#define JVESOURCESITEMSTRUCT_H


#include <QString>


#include "../definitions/jveProjectSourcesItemType.h"
#include "../definitions/jveProjectSourcesItemStatus.h"


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


