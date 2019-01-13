

#include "jveSingleResourceItemModel.h"


#include <QFile>
#include <QCryptographicHash>


#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"

#include "../application/jveApplication.h"
#include "../utils/jveFsUtils.h"


jveSingleResourceItemModel::jveSingleResourceItemModel(
              jveApplication *app,
              QDomElement     domElement,
        const int             type
    ) : jveSourcesItemModel(app, domElement, type)
{
}

jveSingleResourceItemModel::~jveSingleResourceItemModel(void)
{
}

void
jveSingleResourceItemModel::initByResource(const QString &resourcePath)
{
    // absolute path
    mp_itemStruct.absolutePath = jveFsUtils.absolutePathOverDirectory(
        mp_app->projectDirPath(),
        resourcePath
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

    // fill resource struct
    jveSourceResourceStruct resourceStruct(
        mp_itemStruct.absolutePath,
        jveFsUtils.checkFile(
            mp_itemStruct.absolutePath,
            jveFsCheckOption::IsExists | jveFsCheckOption::IsReadable
        )
    );
    // append resource struct to resources list
    mp_itemStruct.resources.append(resourceStruct);

    // item status by resource status
    switch (resourceStruct.status) {
        // not exists
        case jveFsCheckStatus::NotExists:
            mp_itemStruct.status = jveSourcesItemStatus::ResourceNotExists;
        break;
        // not a file
        case jveFsCheckStatus::NotFile:
            mp_itemStruct.status = jveSourcesItemStatus::ResourceNotFile;
        break;
        // not readable
        case jveFsCheckStatus::NotReadable:
            mp_itemStruct.status = jveSourcesItemStatus::ResourceNotReadable;
        break;
    }

    // validate checksum
    if (jveSourcesItemStatus::Ok == mp_itemStruct.status) {
        QFile checkSumFile(resourceStruct.absolutePath);
        if (checkSumFile.open(QFile::ReadOnly)) {
            QCryptographicHash checkSumHash(QCryptographicHash::Md5);
            checkSumHash.addData(&checkSumFile);
            if (mp_itemStruct.checkSum != checkSumHash.result().toHex()) {
                mp_itemStruct.status = jveSourcesItemStatus::ResourceReplaced;
            }
            checkSumFile.close();
        } else {
            mp_itemStruct.status = jveSourcesItemStatus::ErrorReadResource;
        }
    }
}


