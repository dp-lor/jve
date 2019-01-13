

#ifndef JVESOURCESITEMSTRUCT_H
#define JVESOURCESITEMSTRUCT_H


#include <QString>
#include <QVector>


#include "../definitions/jveSourcesItemType.h"
#include "../definitions/jveSourcesItemStatus.h"

#include "jveSourceResourceStruct.h"


struct jveSourcesItemStruct
{
    int     type;
    int     status;
    QString id;
    QString checkSum;
    QString absolutePath;
    QString displayName;
    QString baseName;
    QString searchHaystack;

    // resources
    QVector<jveSourceResourceStruct> resources;

    // empty constructor
    jveSourcesItemStruct(void) :

        type   ( jveSourcesItemType::Undefined ),
        status ( jveSourcesItemStatus::Ok      ),

        id             (),
        checkSum       (),
        absolutePath   (),
        displayName    (),
        baseName       (),
        searchHaystack (),
        resources      ()

    {
    }

    // default constructor
    jveSourcesItemStruct(
        const int      type,
        const QString &id,
        const QString &checkSum
    ) :

        type     ( type                     ),
        status   ( jveSourcesItemStatus::Ok ),
        id       ( id                       ),
        checkSum ( checkSum                 ),

        absolutePath   (),
        displayName    (),
        baseName       (),
        searchHaystack (),
        resources      ()

    {
    }

    // copy constructor
    jveSourcesItemStruct(const jveSourcesItemStruct &other) :

        type           ( other.type           ),
        status         ( other.status         ),
        id             ( other.id             ),
        checkSum       ( other.checkSum       ),
        absolutePath   ( other.absolutePath   ),
        displayName    ( other.displayName    ),
        baseName       ( other.baseName       ),
        searchHaystack ( other.searchHaystack ),

        resources()

    {
        foreach (const jveSourceResourceStruct &resource, other.resources) {
            resources.append(jveSourceResourceStruct(resource));
        }
    }
};


#endif // JVESOURCESITEMSTRUCT_H


