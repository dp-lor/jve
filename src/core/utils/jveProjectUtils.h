

#ifndef JVEPROJECTUTILS_H
#define JVEPROJECTUTILS_H


#include <QFile>


class QDomDocument;


class jveProjectUtils
{
    public:
        static void convertProject(
                  QDomDocument *projectDom,
            const int           fromVersion,
            const int           toVersion
        );
    private:
        static void upgradeProject(
                  QDomDocument *projectDom,
            const int           fromVersion,
            const int           toVersion
        );
        static void downgradeProject(
                  QDomDocument *projectDom,
            const int           fromVersion,
            const int           toVersion
        );
};


#endif // JVEPROJECTUTILS_H


