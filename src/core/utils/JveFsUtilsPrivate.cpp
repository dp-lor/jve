

#include "JveFsUtilsPrivate.h"


#include "../definitions/JveFsCheckOption.h"
#include "../definitions/JveFsCheckStatus.h"
#include "../definitions/JveFsFileFormat.h"


JveFsUtilsPrivate JveFsUtils;


JveFsUtilsPrivate::JveFsUtilsPrivate(void)
    : mp_simpleDir(),
        mp_simpleInfo(),
        mp_targetInfo(),
        mp_parentInfo(),
        mp_mimeDatabase()
{
    mp_simpleInfo.setCaching(false);
    mp_targetInfo.setCaching(false);
    mp_parentInfo.setCaching(false);
}

JveFsUtilsPrivate::~JveFsUtilsPrivate(void)
{
}

bool
JveFsUtilsPrivate::isExists(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.exists();
}

QString
JveFsUtilsPrivate::absolutePath(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.absoluteFilePath();
}

QString
JveFsUtilsPrivate::absolutePathOverDirectory(
    const QString &dirPath,
    const QString &relativePath
)
{
    mp_simpleDir.setPath(dirPath);

    return mp_simpleDir.cleanPath(mp_simpleDir.absoluteFilePath(relativePath));
}

QString
JveFsUtilsPrivate::name(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.fileName();
}

QString
JveFsUtilsPrivate::baseName(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.baseName();
}

QString
JveFsUtilsPrivate::parentPath(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.dir().path();
}

int
JveFsUtilsPrivate::checkFile(
    const QString &filePath,
    const int      checkOptions
)
{
    mp_targetInfo.setFile(filePath);

    return checkTarget(checkOptions, false);
}

int
JveFsUtilsPrivate::checkDirectory(
    const QString &dirPath,
    const int      checkOptions
)
{
    mp_targetInfo.setFile(dirPath);

    return checkTarget(checkOptions, true);
}

int
JveFsUtilsPrivate::fileFormat(const QString &filePath) const
{
    QString mimeTypeName = mp_mimeDatabase.mimeTypeForFile(
        filePath,
        QMimeDatabase::MatchContent
    ).name();

    // TODO maybe Qt::CaseSensitive ???

    // image
    if (0 == mimeTypeName.indexOf("image/", 0, Qt::CaseInsensitive)) {
        return JveFsFileFormat::Image;
    // audio
    } else if (0 == mimeTypeName.indexOf("audio/", 0, Qt::CaseInsensitive)) {
        return JveFsFileFormat::Audio;
    // video
    } else if (0 == mimeTypeName.indexOf("video/", 0, Qt::CaseInsensitive)) {
        return JveFsFileFormat::Video;
    }

    // unsupported
    return JveFsFileFormat::Unsupported;
}

int
JveFsUtilsPrivate::checkTarget(
    const int  checkOptions,
    const bool checkAsDir
)
{
    int parentCheckStatus  = JveFsCheckStatus::Ok;
    int parentCheckOptions = getParentCheckOptions(checkOptions);

    // check parent
    if (JveFsCheckOption::None != parentCheckOptions) {
        parentCheckStatus = checkParent(
            mp_targetInfo.dir().path(),
            parentCheckOptions
        );
        if (JveFsCheckStatus::Ok != parentCheckStatus) {
            return parentCheckStatus;
        }
    }

    // existence check
    if (
        checkOptions & JveFsCheckOption::IsExists
            && !mp_targetInfo.exists()
    ) {
        return JveFsCheckStatus::NotExists;
    }
    // type check
    if (!checkAsDir && !mp_targetInfo.isFile()) {
        return JveFsCheckStatus::NotFile;
    } else if (checkAsDir && !mp_targetInfo.isDir()) {
        return JveFsCheckStatus::NotDirectory;
    }
    // readable check
    if (
        checkOptions & JveFsCheckOption::IsReadable
            && !mp_targetInfo.isReadable()
    ) {
        return JveFsCheckStatus::NotReadable;
    }
    // writable check
    if (
        checkOptions & JveFsCheckOption::IsWritable
            && !mp_targetInfo.isWritable()
    ) {
        return JveFsCheckStatus::NotWritable;
    }

    return JveFsCheckStatus::Ok;
}

int
JveFsUtilsPrivate::checkParent(
    const QString &parentPath,
    const int      checkOptions
)
{
    mp_parentInfo.setFile(parentPath);

    // existence check
    if (
        checkOptions & JveFsCheckOption::IsExists
            && !mp_parentInfo.exists()
    ) {
        return JveFsCheckStatus::ParentNotExists;
    }
    // type check (parent always probably as directory)
    if (!mp_parentInfo.isDir()) {
        return JveFsCheckStatus::ParentNotDirectory;
    }
    // readable check
    if (
        checkOptions & JveFsCheckOption::IsReadable
            && !mp_parentInfo.isReadable()
    ) {
        return JveFsCheckStatus::ParentNotReadable;
    }
    // writable check
    if (
        checkOptions & JveFsCheckOption::IsWritable
            && !mp_parentInfo.isWritable()
    ) {
        return JveFsCheckStatus::ParentNotWritable;
    }

    return JveFsCheckStatus::Ok;
}

int
JveFsUtilsPrivate::getParentCheckOptions(const int checkOptions) const
{
    int parentCheckOptions = JveFsCheckOption::None;

    // add parent existence check
    if (checkOptions & JveFsCheckOption::IsParentExists) {
        parentCheckOptions |= JveFsCheckOption::IsExists;
    }
    // add parent readable check
    if (checkOptions & JveFsCheckOption::IsParentReadable) {
        parentCheckOptions |= JveFsCheckOption::IsReadable;
    }
    // add parent writable check
    if (checkOptions & JveFsCheckOption::IsParentWritable) {
        parentCheckOptions |= JveFsCheckOption::IsWritable;
    }

    return parentCheckOptions;
}


