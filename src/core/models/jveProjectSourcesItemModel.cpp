

#include "jveProjectSourcesItemModel.h"


#include <QFile>
#include <QCryptographicHash>
#include <QDebug>


#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"

#include "../application/jveApplication.h"
#include "../utils/jveFsUtils.h"


jveProjectSourcesItemModel::jveProjectSourcesItemModel(
          jveApplication *app,
          QDomElement     domNode,
    const int             type
) : jveBaseModel(app, domNode),
        mp_id(domNode.attribute("id")),
        mp_checkSum(domNode.attribute("checkSum")),
        mp_type(type)
{
}

jveProjectSourcesItemModel::~jveProjectSourcesItemModel(void)
{
}

void
jveProjectSourcesItemModel::setUp(void)
{
}

void
jveProjectSourcesItemModel::upSet(void)
{
}

QString
jveProjectSourcesItemModel::id(void) const
{
    return mp_id;
}

QString
jveProjectSourcesItemModel::checkSum(void) const
{
    return mp_checkSum;
}

int
jveProjectSourcesItemModel::type(void) const
{
    return mp_type;
}

int
jveProjectSourcesItemModel::status(void) const
{
    return mp_status;
}

jveProjectSourcesItemStruct
jveProjectSourcesItemModel::itemStruct(void) const
{
    jveProjectSourcesItemStruct itemStruct;

    itemStruct.id           = mp_id;
    itemStruct.type         = mp_type;
    itemStruct.status       = mp_status;
    itemStruct.absolutePath = mp_absolutePath;
    itemStruct.name         = mp_name;
    itemStruct.baseName     = mp_baseName;

    return itemStruct;
}

void
jveProjectSourcesItemModel::setId(const QString &id)
{
    mp_id = id;
    mp_domNode.setAttribute("id", mp_id);
}

void
jveProjectSourcesItemModel::setCheckSum(const QString &checkSum)
{
    mp_checkSum = checkSum;
    mp_domNode.setAttribute("checkSum", mp_checkSum);
}

void
jveProjectSourcesItemModel::initEnvironmentBySingleSourceFile(
    const QString &sourcePath
)
{
    mp_absolutePath = jveFsUtils.absolutePathOverDirectory(
        mp_app->projectDirPath(),
        sourcePath
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
    }
}

void
jveProjectSourcesItemModel::initEnvironmentBySourceFilesSequence(
    const QStringList &sources
)
{
    // empty
    if (0 == sources.size()) {

        mp_status       = jveProjectSourcesItemStatus::EmptySequence;
        mp_absolutePath = "";
        mp_name         = "";
        mp_baseName     = "";

    // not empty
    } else {

        mp_absolutePath = jveFsUtils.parentPath(
            jveFsUtils.absolutePathOverDirectory(
                mp_app->projectDirPath(),
                sources.at(0)
            )
        );

        if (1 == sources.size()) {
            mp_name = jveFsUtils.name(mp_absolutePath)
                + " (..."
                + jveFsUtils.name(sources.at(0))
                + "...)";
        } else {
            mp_name = jveFsUtils.name(mp_absolutePath)
                + " ("
                + jveFsUtils.name(sources.first())
                + "..."
                + jveFsUtils.name(sources.last())
                + ")";
        }

        mp_baseName = jveFsUtils.name(mp_absolutePath);

        foreach (const QString &sourcePath, sources) {
            mp_baseName += jveFsUtils.baseName(sourcePath);
        }

    }


    /*mp_absolutePath = jveFsUtils.absolutePathOverDirectory(
        mp_app->projectDirPath(),
        sourcePath
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


