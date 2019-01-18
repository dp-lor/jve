

#include "JveProjectUtils.h"


#include <QDomDocument>


#include "../definitions/JveProjectVersion.h"


void
JveProjectUtils::convertProject(
          QDomDocument *projectDom,
    const int           fromVersion,
    const int           toVersion
)
{
    if (fromVersion < toVersion) {
        JveProjectUtils::upgradeProject(
            projectDom,
            fromVersion,
            fromVersion + 1
        );
    } else if (fromVersion > toVersion) {
        JveProjectUtils::downgradeProject(
            projectDom,
            fromVersion,
            fromVersion - 1
        );
    }
}

void
JveProjectUtils::upgradeProject(
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
JveProjectUtils::downgradeProject(
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


