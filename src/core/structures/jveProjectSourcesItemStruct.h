

#ifndef JVEPROJECTSOURCESITEMSTRUCT_H
#define JVEPROJECTSOURCESITEMSTRUCT_H


#include <QString>


#include "../definitions/jveProjectSourcesItemType.h"
#include "../definitions/jveProjectSourcesItemStatus.h"


typedef struct _jveProjectSourcesItemStruct
{
    QString id;
    int     type;
    int     status;
    QString absolutePath;
    QString name;
    QString baseName;
} jveProjectSourcesItemStruct;


#endif // JVEPROJECTSOURCESITEMSTRUCT_H


