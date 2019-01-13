

#include "jveMultipleResourcesItemModel.h"


#include <QFile>
#include <QCryptographicHash>


#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"

#include "../application/jveApplication.h"
#include "../utils/jveFsUtils.h"


jveMultipleResourcesItemModel::jveMultipleResourcesItemModel(
              jveApplication *app,
              QDomElement     domElement,
        const int             type
    ) : jveSourcesItemModel(app, domElement, type)
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
    // absolute path
    mp_itemStruct.absolutePath = jveFsUtils.absolutePathOverDirectory(
        mp_app->projectDirPath(),
        resourcesDirPath
    );
    // display name
    mp_itemStruct.displayName = jveFsUtils.name(mp_itemStruct.absolutePath);
    // base name
    mp_itemStruct.baseName = jveFsUtils.baseName(mp_itemStruct.absolutePath);
    if (0 == mp_itemStruct.baseName.size()) {
        mp_itemStruct.baseName = mp_itemStruct.displayName;
    }
    // search haystack
    mp_itemStruct.searchHaystack = mp_itemStruct.baseName;

    // empty resources list
    if (0 == resourcesList.size()) {

        mp_itemStruct.status       = jveSourcesItemStatus::EmptyResourcesList;
        mp_itemStruct.displayName += " (...)";

        return;
    }

    ////////////////////////////////////////////////////////////////////////////

    // one resource
    if (1 == resourcesList.size()) {
        mp_itemStruct.displayName += " (...";
        mp_itemStruct.displayName += jveFsUtils.name(resourcesList.at(0));
        mp_itemStruct.displayName += "...)";
    // many resources
    } else {
        mp_itemStruct.displayName += " (";
        mp_itemStruct.displayName += jveFsUtils.name(resourcesList.first());
        mp_itemStruct.displayName += "...";
        mp_itemStruct.displayName += jveFsUtils.name(resourcesList.last());
        mp_itemStruct.displayName += ")";
    }

    ////////////////////////////////////////////////////////////////////////////

    QString            absoluteResourcePath;
    QString            resourceName;
    QCryptographicHash checkSumHash(QCryptographicHash::Md5);
    QFile              checkSumFile;

    // check resources
    foreach (const QString &resourcePath, resourcesList) {

        absoluteResourcePath = jveFsUtils.absolutePathOverDirectory(
            mp_itemStruct.absolutePath,
            jveFsUtils.name(resourcePath)
        );

        // fill resource struct
        jveSourceResourceStruct resourceStruct(
            absoluteResourcePath,
            jveFsUtils.checkFile(
                absoluteResourcePath,
                jveFsCheckOption::IsExists | jveFsCheckOption::IsReadable
            )
        );
        // append resource struct to resources list
        mp_itemStruct.resources.append(resourceStruct);

        // append names for search
        resourceName = jveFsUtils.baseName(resourceStruct.absolutePath);
        if (0 == resourceName.size()) {
            resourceName = jveFsUtils.name(resourceStruct.absolutePath);
        }
        mp_itemStruct.searchHaystack += resourceName;

        // item status by resource status (change once)
        if (jveSourcesItemStatus::Ok == mp_itemStruct.status) {
            switch (resourceStruct.status) {
                // not exists
                case jveFsCheckStatus::NotExists:
                    mp_itemStruct.status
                        = jveSourcesItemStatus::SeveralResourcesNotExists;
                break;
                // not a file
                case jveFsCheckStatus::NotFile:
                    mp_itemStruct.status
                        = jveSourcesItemStatus::SeveralResourcesNotFile;
                break;
                // not readable
                case jveFsCheckStatus::NotReadable:
                    mp_itemStruct.status
                        = jveSourcesItemStatus::SeveralResourcesNotReadable;
                break;
            }
        }

        // add resource file data to checksum
        if (
            jveSourcesItemStatus::Ok == mp_itemStruct.status
                && jveFsCheckStatus::Ok == resourceStruct.status
        ) {
            checkSumFile.close();
            checkSumFile.setFileName(resourceStruct.absolutePath);
            if (checkSumFile.open(QFile::ReadOnly)) {
                checkSumHash.addData(&checkSumFile);
                checkSumFile.close();
            } else {
                mp_itemStruct.status
                    = jveSourcesItemStatus::ErrorReadSeveralResources;
            }
        }
    }

    // when several resources not ok
    if (jveSourcesItemStatus::Ok != mp_itemStruct.status) {
        return;
    }

    ////////////////////////////////////////////////////////////////////////////

    // validate checksum
    if (mp_itemStruct.checkSum != checkSumHash.result().toHex()) {
        mp_itemStruct.status = jveSourcesItemStatus::SeveralResourcesReplaced;
    }
}


