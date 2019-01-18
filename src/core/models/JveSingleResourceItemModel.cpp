

#include "JveSingleResourceItemModel.h"


#include <QFile>
#include <QCryptographicHash>


#include "../definitions/JveFsCheckOption.h"
#include "../definitions/JveFsCheckStatus.h"

#include "../application/JveProject.h"
#include "../utils/JveFsUtils.h"


JveSingleResourceItemModel::JveSingleResourceItemModel(
              JveProject  *project,
              QDomElement  domElement,
        const int          type
    ) : JveSourcesItemModel(project, domElement, type)
{
}

JveSingleResourceItemModel::~JveSingleResourceItemModel(void)
{
}

void
JveSingleResourceItemModel::initByResource(const QString &resourcePath)
{
    // absolute path
    mp_itemStruct.absolutePath = JveFsUtils.absolutePathOverDirectory(
        mp_project->parentDirPath(),
        resourcePath
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

    // fill resource struct
    JveSourceResourceStruct resourceStruct(
        mp_itemStruct.absolutePath,
        JveFsUtils.checkFile(
            mp_itemStruct.absolutePath,
            JveFsCheckOption::IsExists | JveFsCheckOption::IsReadable
        )
    );
    // append resource struct to resources list
    mp_itemStruct.resources.append(resourceStruct);

    // item status by resource status
    switch (resourceStruct.status) {
        // not exists
        case JveFsCheckStatus::NotExists:
            mp_itemStruct.status = JveSourcesItemStatus::ResourceNotExists;
        break;
        // not a file
        case JveFsCheckStatus::NotFile:
            mp_itemStruct.status = JveSourcesItemStatus::ResourceNotFile;
        break;
        // not readable
        case JveFsCheckStatus::NotReadable:
            mp_itemStruct.status = JveSourcesItemStatus::ResourceNotReadable;
        break;
    }

    // validate checksum
    if (JveSourcesItemStatus::Ok == mp_itemStruct.status) {
        QFile checkSumFile(resourceStruct.absolutePath);
        if (checkSumFile.open(QFile::ReadOnly)) {
            QCryptographicHash checkSumHash(QCryptographicHash::Md5);
            checkSumHash.addData(&checkSumFile);
            if (mp_itemStruct.checkSum != checkSumHash.result().toHex()) {
                mp_itemStruct.status = JveSourcesItemStatus::ResourceReplaced;
            }
            checkSumFile.close();
        } else {
            mp_itemStruct.status = JveSourcesItemStatus::ErrorReadResource;
        }
    }
}


