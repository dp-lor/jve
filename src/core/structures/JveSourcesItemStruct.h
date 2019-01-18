

#ifndef JVESOURCESITEMSTRUCT_H
#define JVESOURCESITEMSTRUCT_H


#include <QString>
#include <QVector>


#include "../definitions/JveSourcesItemType.h"
#include "../definitions/JveSourcesItemStatus.h"

#include "JveSourceResourceStruct.h"


struct JveSourcesItemStruct
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
    QVector<JveSourceResourceStruct> resources;

    // empty constructor
    JveSourcesItemStruct(void) :

        type   ( JveSourcesItemType::Undefined ),
        status ( JveSourcesItemStatus::Ok      ),

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
    JveSourcesItemStruct(
        const int      type,
        const QString &id,
        const QString &checkSum
    ) :

        type     ( type                     ),
        status   ( JveSourcesItemStatus::Ok ),
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
    JveSourcesItemStruct(const JveSourcesItemStruct &other) :

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
        foreach (const JveSourceResourceStruct &resource, other.resources) {
            resources.append(JveSourceResourceStruct(resource));
        }
    }
};


#endif // JVESOURCESITEMSTRUCT_H


