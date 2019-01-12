

#include "jveSingleResourceItemModel.h"


#include <QFile>
#include <QCryptographicHash>


#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"

#include "../application/jveApplication.h"
#include "../utils/jveFsUtils.h"


jveSingleResourceItemModel::jveSingleResourceItemModel(
              jveApplication *app,
              QDomElement     domNode,
        const int             type
    ) : jveSourcesItemModel(app, domNode, type)
{
}

jveSingleResourceItemModel::~jveSingleResourceItemModel(void)
{
}

void
jveSingleResourceItemModel::initByResource(const QString &resourcePath)
{
    jveSourceResourceStruct resourceStruct;

    mp_absolutePath = jveFsUtils.absolutePathOverDirectory(
        mp_app->projectDirPath(),
        resourcePath
    );
    mp_displayName    = jveFsUtils.name(mp_absolutePath);
    mp_searchHaystack = jveFsUtils.baseName(mp_absolutePath);
    if (0 == mp_searchHaystack.size()) {
        mp_searchHaystack = jveFsUtils.name(mp_absolutePath);
    }

    // fill resource struct
    resourceStruct.status = jveFsUtils.checkFile(
        mp_absolutePath,
        jveFsCheckOption::IsExists | jveFsCheckOption::IsReadable
    );
    resourceStruct.absolutePath = mp_absolutePath;

    // set sources item status by resource status
    switch (resourceStruct.status) {
        // not exists
        case jveFsCheckStatus::NotExists:
            mp_status = jveSourcesItemStatus::ResourceNotExists;
        break;
        // not a file
        case jveFsCheckStatus::NotFile:
            mp_status = jveSourcesItemStatus::ResourceNotFile;
        break;
        // not readable
        case jveFsCheckStatus::NotReadable:
            mp_status = jveSourcesItemStatus::ResourceNotReadable;
        break;
    }

    // validate checksum
    if (jveSourcesItemStatus::Ok == mp_status) {
        QFile checkSumFile(resourceStruct.absolutePath);
        if (checkSumFile.open(QFile::ReadOnly)) {
            QCryptographicHash checkSumHash(QCryptographicHash::Md5);
            checkSumHash.addData(&checkSumFile);
            if (mp_checkSum != checkSumHash.result().toHex()) {
                mp_status = jveSourcesItemStatus::ResourceReplaced;
            }
            checkSumFile.close();
        } else {
            mp_status = jveSourcesItemStatus::ErrorReadResource;
        }
    }

    // append resource struct to list
    mp_resourcesStructList.append(resourceStruct);
}


