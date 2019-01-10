

#include "jveFsUtilsPrivate.h"


#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"


jveFsUtilsPrivate jveFsUtils;


jveFsUtilsPrivate::jveFsUtilsPrivate(void)
    : mp_simpleDir(),
        mp_simpleInfo(),
        mp_targetInfo(),
        mp_parentInfo()
{
    mp_simpleInfo.setCaching(false);
    mp_targetInfo.setCaching(false);
    mp_parentInfo.setCaching(false);
}

jveFsUtilsPrivate::~jveFsUtilsPrivate(void)
{
}

bool
jveFsUtilsPrivate::isExists(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.exists();
}

QString
jveFsUtilsPrivate::absolutePath(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.absoluteFilePath();
}

QString
jveFsUtilsPrivate::absolutePathOverDirectory(
    const QString &dirPath,
    const QString &relativePath
)
{
    mp_simpleDir.setPath(dirPath);

    return mp_simpleDir.cleanPath(mp_simpleDir.absoluteFilePath(relativePath));
}

QString
jveFsUtilsPrivate::name(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.fileName();
}

QString
jveFsUtilsPrivate::baseName(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.baseName();
}

QString
jveFsUtilsPrivate::parentPath(const QString &targetPath)
{
    mp_simpleInfo.setFile(targetPath);

    return mp_simpleInfo.dir().path();
}

int
jveFsUtilsPrivate::checkFile(
    const QString &filePath,
    const int      checkOptions
)
{
    mp_targetInfo.setFile(filePath);

    return checkTarget(checkOptions, false);
}

int
jveFsUtilsPrivate::checkDirectory(
    const QString &dirPath,
    const int      checkOptions
)
{
    mp_targetInfo.setFile(dirPath);

    return checkTarget(checkOptions, true);
}

int
jveFsUtilsPrivate::checkTarget(
    const int  checkOptions,
    const bool checkAsDir
)
{
    int parentCheckStatus  = jveFsCheckStatus::Ok;
    int parentCheckOptions = getParentCheckOptions(checkOptions);

    // check parent
    if (jveFsCheckOption::None != parentCheckOptions) {
        parentCheckStatus = checkParent(
            mp_targetInfo.dir().path(),
            parentCheckOptions
        );
        if (jveFsCheckStatus::Ok != parentCheckStatus) {
            return parentCheckStatus;
        }
    }

    // existence check
    if (
        checkOptions & jveFsCheckOption::IsExists
            && !mp_targetInfo.exists()
    ) {
        return jveFsCheckStatus::NotExists;
    }
    // type check
    if (!checkAsDir && !mp_targetInfo.isFile()) {
        return jveFsCheckStatus::NotFile;
    } else if (checkAsDir && !mp_targetInfo.isDir()) {
        return jveFsCheckStatus::NotDirectory;
    }
    // readable check
    if (
        checkOptions & jveFsCheckOption::IsReadable
            && !mp_targetInfo.isReadable()
    ) {
        return jveFsCheckStatus::NotReadable;
    }
    // writable check
    if (
        checkOptions & jveFsCheckOption::IsWritable
            && !mp_targetInfo.isWritable()
    ) {
        return jveFsCheckStatus::NotWritable;
    }

    return jveFsCheckStatus::Ok;
}

int
jveFsUtilsPrivate::checkParent(
    const QString &parentPath,
    const int      checkOptions
)
{
    mp_parentInfo.setFile(parentPath);

    // existence check
    if (
        checkOptions & jveFsCheckOption::IsExists
            && !mp_parentInfo.exists()
    ) {
        return jveFsCheckStatus::ParentNotExists;
    }
    // type check (parent always probably as directory)
    if (!mp_parentInfo.isDir()) {
        return jveFsCheckStatus::ParentNotDirectory;
    }
    // readable check
    if (
        checkOptions & jveFsCheckOption::IsReadable
            && !mp_parentInfo.isReadable()
    ) {
        return jveFsCheckStatus::ParentNotReadable;
    }
    // writable check
    if (
        checkOptions & jveFsCheckOption::IsWritable
            && !mp_parentInfo.isWritable()
    ) {
        return jveFsCheckStatus::ParentNotWritable;
    }

    return jveFsCheckStatus::Ok;
}

int
jveFsUtilsPrivate::getParentCheckOptions(const int checkOptions) const
{
    int parentCheckOptions = jveFsCheckOption::None;

    // add parent existence check
    if (checkOptions & jveFsCheckOption::IsParentExists) {
        parentCheckOptions |= jveFsCheckOption::IsExists;
    }
    // add parent readable check
    if (checkOptions & jveFsCheckOption::IsParentReadable) {
        parentCheckOptions |= jveFsCheckOption::IsReadable;
    }
    // add parent writable check
    if (checkOptions & jveFsCheckOption::IsParentWritable) {
        parentCheckOptions |= jveFsCheckOption::IsWritable;
    }

    return parentCheckOptions;
}


