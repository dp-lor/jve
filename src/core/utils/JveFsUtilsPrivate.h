

#ifndef JVEFSUTILSPRIVATE_H
#define JVEFSUTILSPRIVATE_H


#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QMimeDatabase>


class JveFsUtilsPrivate
{
    public:
        explicit  JveFsUtilsPrivate(void);
        virtual  ~JveFsUtilsPrivate(void);
    public:
        bool isExists(const QString &targetPath);
        QString absolutePath(const QString &targetPath);
        QString absolutePathOverDirectory(
            const QString &absoluteDirPath,
            const QString &relativeTargetPath
        );
        QString relativePathOverDirectory(
            const QString &absoluteDirPath,
            const QString &absoluteTargetPath
        );
    public:
        QString name(const QString &targetPath);
        QString baseName(const QString &targetPath);
    public:
        QString parentPath(const QString &targetPath);
    public:
        int checkFile(const QString &filePath, const int checkOptions);
        int checkDirectory(const QString &dirPath, const int checkOptions);
    public:
        int fileFormat(const QString &filePath) const;
    private:
        int checkTarget(const int checkOptions, const bool checkAsDir);
        int checkParent(const QString &parentPath, const int checkOptions);
        int getParentCheckOptions(const int checkOptions) const;
    private:
        // members
        QDir          mp_simpleDir;
        QFileInfo     mp_simpleInfo;
        QFileInfo     mp_targetInfo;
        QFileInfo     mp_parentInfo;
        QMimeDatabase mp_mimeDatabase;
};


#endif // JVEFSUTILSPRIVATE_H


