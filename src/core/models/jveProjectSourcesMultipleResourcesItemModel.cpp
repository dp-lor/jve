

#include "jveProjectSourcesMultipleResourcesItemModel.h"


#include <QFile>
#include <QCryptographicHash>


#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"

#include "../application/jveApplication.h"
#include "../utils/jveFsUtils.h"


jveProjectSourcesMultipleResourcesItemModel
    ::jveProjectSourcesMultipleResourcesItemModel(
              jveApplication *app,
              QDomElement     domNode,
        const int             type
    ) : jveSourcesItemModel(app, domNode, type)
{
}

jveProjectSourcesMultipleResourcesItemModel
    ::~jveProjectSourcesMultipleResourcesItemModel(void)
{
}

void
jveProjectSourcesMultipleResourcesItemModel::initByResources(
    const QStringList &resourcesList
)
{
    // empty
    if (0 == resourcesList.size()) {

        mp_status       = jveProjectSourcesItemStatus::EmptySequence;
        mp_absolutePath = "";
        mp_name         = "";
        mp_baseName     = "";

    // not empty
    } else {

        mp_absolutePath = jveFsUtils.parentPath(
            jveFsUtils.absolutePathOverDirectory(
                mp_app->projectDirPath(),
                resourcesList.at(0)
            )
        );

        if (1 == resourcesList.size()) {
            mp_name = jveFsUtils.name(mp_absolutePath)
                + " (..."
                + jveFsUtils.name(resourcesList.at(0))
                + "...)";
        } else {
            mp_name = jveFsUtils.name(mp_absolutePath)
                + " ("
                + jveFsUtils.name(resourcesList.first())
                + "..."
                + jveFsUtils.name(resourcesList.last())
                + ")";
        }

        mp_baseName = jveFsUtils.name(mp_absolutePath);

        foreach (const QString &resourcePath, resourcesList) {
            mp_baseName += jveFsUtils.baseName(resourcePath);
        }

    }

    /*mp_absolutePath = jveFsUtils.absolutePathOverDirectory(
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
            mp_status = jveProjectSourcesItemStatus::NotExists;
        break;
        // not a file
        case jveFsCheckStatus::NotFile:
            mp_status = jveProjectSourcesItemStatus::NotFile;
        break;
        // not readable
        case jveFsCheckStatus::NotReadable:
            mp_status = jveProjectSourcesItemStatus::NotReadable;
        break;
        // ok
        default:
            mp_status = jveProjectSourcesItemStatus::Ok;
        break;
    }

    // validate checksum
    if (jveProjectSourcesItemStatus::Ok == mp_status) {
        QFile checksumFile(mp_absolutePath);
        if (checksumFile.open(QFile::ReadOnly)) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(&checksumFile);
            if (mp_checkSum != hash.result().toHex()) {
                mp_status = jveProjectSourcesItemStatus::Replaced;
            }
            checksumFile.close();
        } else {
            mp_status = jveProjectSourcesItemStatus::NotExists;
        }
    }*/
}


