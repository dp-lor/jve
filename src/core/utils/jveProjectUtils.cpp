

#include "jveProjectUtils.h"


#include <QDomDocument>


#include "../definitions/jveProjectVersion.h"


void
jveProjectUtils::convertProject(
          QDomDocument *projectDom,
    const int           fromVersion,
    const int           toVersion
)
{
    if (fromVersion < toVersion) {
        jveProjectUtils::upgradeProject(
            projectDom,
            fromVersion,
            fromVersion + 1
        );
    } else if (fromVersion > toVersion) {
        jveProjectUtils::downgradeProject(
            projectDom,
            fromVersion,
            fromVersion - 1
        );
    }
}

void
jveProjectUtils::upgradeProject(
          QDomDocument *projectDom,
    const int           fromVersion,
    const int           toVersion
)
{
    // only one supported version now
    Q_UNUSED(projectDom);
    Q_UNUSED(fromVersion);
    Q_UNUSED(toVersion);
}

void
jveProjectUtils::downgradeProject(
          QDomDocument *projectDom,
    const int           fromVersion,
    const int           toVersion
)
{
    // only one supported version now
    Q_UNUSED(projectDom);
    Q_UNUSED(fromVersion);
    Q_UNUSED(toVersion);
}


