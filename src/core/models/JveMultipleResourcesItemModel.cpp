

#include "JveMultipleResourcesItemModel.h"


#include <QFile>
#include <QCryptographicHash>


#include "../definitions/JveFsCheckOption.h"
#include "../definitions/JveFsCheckStatus.h"

#include "../application/JveProject.h"
#include "../utils/JveFsUtils.h"


JveMultipleResourcesItemModel::JveMultipleResourcesItemModel(
              JveProject  *project,
              QDomElement  domElement,
        const int          type
    ) : JveSourcesItemModel(project, domElement, type)
{
}

JveMultipleResourcesItemModel::~JveMultipleResourcesItemModel(void)
{
}

void
JveMultipleResourcesItemModel::initByResources(
    const QString     &resourcesDirPath,
    const QStringList &resourcesList
)
{
    // absolute path
    mp_itemStruct.absolutePath = JveFsUtils.absolutePathOverDirectory(
        "",//mp_project->parentDirPath(),
        resourcesDirPath
    );
    // display name
    mp_itemStruct.displayName = JveFsUtils.name(mp_itemStruct.absolutePath);
    // base name
    mp_itemStruct.baseName = JveFsUtils.baseName(mp_itemStruct.absolutePath);
    if (0 == mp_itemStruct.baseName.size()) {
        mp_itemStruct.baseName = mp_itemStruct.displayName;
    }
    // search haystack
    mp_itemStruct.searchHaystack = mp_itemStruct.baseName;

    // empty resources list
    if (0 == resourcesList.size()) {

        mp_itemStruct.status       = JveSourcesItemStatus::EmptyResourcesList;
        mp_itemStruct.displayName += " (...)";

        return;
    }

    /**********************************************************/

    // one resource
    if (1 == resourcesList.size()) {
        mp_itemStruct.displayName += " (...";
        mp_itemStruct.displayName += JveFsUtils.name(resourcesList.at(0));
        mp_itemStruct.displayName += "...)";
    // many resources
    } else {
        mp_itemStruct.displayName += " (";
        mp_itemStruct.displayName += JveFsUtils.name(resourcesList.first());
        mp_itemStruct.displayName += "...";
        mp_itemStruct.displayName += JveFsUtils.name(resourcesList.last());
        mp_itemStruct.displayName += ")";
    }

    /**********************************************************/

    QString            absoluteResourcePath;
    QString            resourceName;
    QCryptographicHash checkSumHash(QCryptographicHash::Md5);
    QFile              checkSumFile;

    // check resources
    foreach (const QString &resourcePath, resourcesList) {

        absoluteResourcePath = JveFsUtils.absolutePathOverDirectory(
            mp_itemStruct.absolutePath,
            JveFsUtils.name(resourcePath)
        );

        // fill resource struct
        JveSourceResourceStruct resourceStruct(
            absoluteResourcePath,
            JveFsUtils.checkFile(
                absoluteResourcePath,
                JveFsCheckOption::IsExists | JveFsCheckOption::IsReadable
            )
        );

        // append names for search
        resourceName = JveFsUtils.baseName(resourceStruct.absolutePath);
        if (0 == resourceName.size()) {
            resourceName = JveFsUtils.name(resourceStruct.absolutePath);
        }
        mp_itemStruct.searchHaystack += resourceName;

        // item status by resource status (change once)
        if (JveSourcesItemStatus::Ok == mp_itemStruct.status) {
            switch (resourceStruct.status) {
                // not exists
                case JveFsCheckStatus::NotExists:
                    mp_itemStruct.status
                        = JveSourcesItemStatus::SeveralResourcesNotExists;
                break;
                // not a file
                case JveFsCheckStatus::NotFile:
                    mp_itemStruct.status
                        = JveSourcesItemStatus::SeveralResourcesNotFile;
                break;
                // not readable
                case JveFsCheckStatus::NotReadable:
                    mp_itemStruct.status
                        = JveSourcesItemStatus::SeveralResourcesNotReadable;
                break;
            }
        }

        if (
            JveSourcesItemStatus::Ok == mp_itemStruct.status
                && JveFsCheckStatus::Ok == resourceStruct.status
        ) {

            // detect format
            resourceStruct.format
                = JveFsUtils.fileFormat(resourceStruct.absolutePath);

            // add resource file data to checksum
            checkSumFile.close();
            checkSumFile.setFileName(resourceStruct.absolutePath);
            if (checkSumFile.open(QFile::ReadOnly)) {
                checkSumHash.addData(&checkSumFile);
                checkSumFile.close();
            } else {
                mp_itemStruct.status
                    = JveSourcesItemStatus::ErrorReadSeveralResources;
            }

        }

        // append resource struct to resources list
        mp_itemStruct.resources.append(resourceStruct);
    }

    // when several resources not ok
    if (JveSourcesItemStatus::Ok != mp_itemStruct.status) {
        return;
    }

    /**********************************************************/

    // validate checksum
    if (mp_itemStruct.checkSum != checkSumHash.result().toHex()) {
        mp_itemStruct.status = JveSourcesItemStatus::SeveralResourcesReplaced;
    }
}


