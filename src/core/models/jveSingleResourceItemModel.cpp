

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
    mp_absolutePath = jveFsUtils.absolutePathOverDirectory(
        mp_app->projectDirPath(),
        resourcePath
    );
    mp_name     = jveFsUtils.name(mp_absolutePath);
    mp_baseName = jveFsUtils.baseName(mp_absolutePath);

    // ckeck source file
    int status = jveFsUtils.checkFile(
        mp_absolutePath,
        jveFsCheckOption::IsExists | jveFsCheckOption::IsReadable
    );

    // set source status
    switch (status) {
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
        // ok
        default:
            mp_status = jveSourcesItemStatus::Ok;
        break;
    }

    // validate checksum
    if (jveSourcesItemStatus::Ok == mp_status) {
        QFile checksumFile(mp_absolutePath);
        if (checksumFile.open(QFile::ReadOnly)) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(&checksumFile);
            if (mp_checkSum != hash.result().toHex()) {
                mp_status = jveSourcesItemStatus::ResourceReplaced;
            }
            checksumFile.close();
        } else {
            mp_status = jveSourcesItemStatus::ResourceNotExists;
        }
    }
}


