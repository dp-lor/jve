

#ifndef JVEFSUTILSPRIVATE_H
#define JVEFSUTILSPRIVATE_H


#include <QString>
#include <QDir>
#include <QFileInfo>


class jveFsUtilsPrivate
{
    public:
        explicit  jveFsUtilsPrivate(void);
        virtual  ~jveFsUtilsPrivate(void);
    public:
        bool    isExists(const QString &targetPath);
        QString absolutePath(const QString &targetPath);
        QString absolutePathOverDirectory(
            const QString &dirPath,
            const QString &relativePath
        );
    public:
        QString name(const QString &targetPath);
        QString baseName(const QString &targetPath);
    public:
        QString parentPath(const QString &targetPath);
    public:
        int checkFile(const QString &filePath, const int checkOptions);
        int checkDirectory(const QString &dirPath, const int checkOptions);
    private:
        int checkTarget(const int checkOptions, const bool checkAsDir);
        int checkParent(const QString &parentPath, const int checkOptions);
        int getParentCheckOptions(const int checkOptions) const;
    private:
        // members
        QDir      mp_simpleDir;
        QFileInfo mp_simpleInfo;
        QFileInfo mp_targetInfo;
        QFileInfo mp_parentInfo;
};


#endif // JVEFSUTILSPRIVATE_H


