

#include "jveMultipleResourcesItemModel.h"


#include <QFile>
#include <QCryptographicHash>


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
    mp_displayName    = jveFsUtils.name(mp_absolutePath);
    mp_searchHaystack = jveFsUtils.baseName(mp_absolutePath);
    if (0 == mp_searchHaystack.size()) {
        mp_searchHaystack = jveFsUtils.name(mp_absolutePath);
    }

    // empty
    if (0 == resourcesList.size()) {
        mp_status       = jveSourcesItemStatus::EmptyResourcesList;
        mp_displayName += " (...)";
    // one
    } else if (1 == resourcesList.size()) {
        mp_displayName += " (...";
        mp_displayName += jveFsUtils.name(resourcesList.at(0));
        mp_displayName += "...)";
    // many
    } else {
        mp_displayName += " (";
        mp_displayName += jveFsUtils.name(resourcesList.first());
        mp_displayName += "...";
        mp_displayName += jveFsUtils.name(resourcesList.last());
        mp_displayName += ")";
    }

    // when empty resources list
    if (jveSourcesItemStatus::Ok != mp_status) {
        return;
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

        if (jveSourcesItemStatus::Ok == mp_status) {
            // set sources item status by resource status
            switch (resourceStruct.status) {
                // not exists
                case jveFsCheckStatus::NotExists:
                    mp_status
                        = jveSourcesItemStatus::SeveralResourcesNotExists;
                break;
                // not a file
                case jveFsCheckStatus::NotFile:
                    mp_status
                        = jveSourcesItemStatus::SeveralResourcesNotFile;
                break;
                // not readable
                case jveFsCheckStatus::NotReadable:
                    mp_status
                        = jveSourcesItemStatus::SeveralResourcesNotReadable;
                break;
            }
        }

        // add resource file data to checksum
        if (
            jveSourcesItemStatus::Ok == mp_status
                && jveFsCheckStatus::Ok == resourceStruct.status
        ) {
            checkSumFile.close();
            checkSumFile.setFileName(resourceStruct.absolutePath);
            if (checkSumFile.open(QFile::ReadOnly)) {
                checkSumHash.addData(&checkSumFile);
                checkSumFile.close();
            } else {
                mp_status = jveSourcesItemStatus::ErrorReadSeveralResources;
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

    // when one or more resources not ok
    if (jveSourcesItemStatus::Ok != mp_status) {
        return;
    }

    // validate checksum
    if (mp_checkSum != checkSumHash.result().toHex()) {
        mp_status = jveSourcesItemStatus::SeveralResourcesReplaced;
    }
}


