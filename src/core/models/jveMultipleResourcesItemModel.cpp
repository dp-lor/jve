

#include "jveMultipleResourcesItemModel.h"


#include <QFile>
#include <QCryptographicHash>
#include <QDebug>


#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"

#include "../application/jveApplication.h"
#include "../utils/jveFsUtils.h"


jveMultipleResourcesItemModel::jveMultipleResourcesItemModel(
              jveApplication *app,
              QDomElement     domNode,
        const int             type
    ) : jveSourcesItemModel(app, domNode, type)
{
}

jveMultipleResourcesItemModel::~jveMultipleResourcesItemModel(void)
{
}

void
jveMultipleResourcesItemModel::initByResources(
    const QString     &resourcesDirPath,
    const QStringList &resourcesList
)
{
    QCryptographicHash checkSumHash(QCryptographicHash::Md5);
    QFile              checkSumFile;

    mp_absolutePath = jveFsUtils.absolutePathOverDirectory(
        mp_app->projectDirPath(),
        resourcesDirPath
    );
    mp_name           = jveFsUtils.name(mp_absolutePath);
    mp_searchHaystack = jveFsUtils.baseName(mp_absolutePath);
    if (0 == mp_searchHaystack.size()) {
        mp_searchHaystack = jveFsUtils.name(mp_absolutePath);
    }

    // empty
    if (0 == resourcesList.size()) {
        mp_status |= jveSourcesItemStatus::EmptyResourcesList;
        mp_name   += " (...)";
    // one
    } else if (1 == resourcesList.size()) {
        mp_name += " (...";
        mp_name += jveFsUtils.name(resourcesList.at(0));
        mp_name += "...)";
    // many
    } else {
        mp_name += " (";
        mp_name += jveFsUtils.name(resourcesList.first());
        mp_name += "...";
        mp_name += jveFsUtils.name(resourcesList.last());
        mp_name += ")";
    }

    // check resources
    foreach (const QString &resourcePath, resourcesList) {
        jveSourceResourceStruct resourceStruct;

        // fill resource struct
        resourceStruct.absolutePath = jveFsUtils.absolutePathOverDirectory(
            mp_absolutePath,
            jveFsUtils.name(resourcePath)
        );
        resourceStruct.status = jveFsUtils.checkFile(
            resourceStruct.absolutePath,
            jveFsCheckOption::IsExists | jveFsCheckOption::IsReadable
        );

        // fill sources item status by resource status
        switch (resourceStruct.status) {
            // not exists
            case jveFsCheckStatus::NotExists:
                mp_status |= jveSourcesItemStatus::ResourceNotExists;
            break;
            // not a file
            case jveFsCheckStatus::NotFile:
                mp_status |= jveSourcesItemStatus::ResourceNotFile;
            break;
            // not readable
            case jveFsCheckStatus::NotReadable:
                mp_status |= jveSourcesItemStatus::ResourceNotReadable;
            break;
        }

        // add resource file data to checksum
        if (jveFsCheckStatus::Ok == resourceStruct.status) {
            checkSumFile.close();
            checkSumFile.setFileName(resourceStruct.absolutePath);
            if (checkSumFile.open(QFile::ReadOnly)) {
                checkSumHash.addData(&checkSumFile);
                checkSumFile.close();
            } else {
                mp_status |= jveSourcesItemStatus::ResourceNotExists;
            }
        }

        // append resource struct to list
        mp_resourcesStructList.append(resourceStruct);
        // append names for search
        QString resourceName = jveFsUtils.baseName(resourceStruct.absolutePath);
        if (0 == resourceName.size()) {
            resourceName = jveFsUtils.name(resourceStruct.absolutePath);
        }
        mp_searchHaystack += resourceName;
    }

    // validate checksum
    if (mp_checkSum != checkSumHash.result().toHex()) {
        mp_status |= jveSourcesItemStatus::ResourceReplaced;
    }
}


