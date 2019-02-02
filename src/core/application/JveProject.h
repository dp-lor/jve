

#ifndef JVEPROJECT_H
#define JVEPROJECT_H


#include <QString>


class JveProject
{
    public:
        static void close(void);
        static void loadNew(void);
        static void loadXmlToDom(const QString &filePath);
        static void validateIds(void);
        static void validateReferences(void);
        static void createModels(void);
        static void initSources(void);
        static void save(const QString &filePath);
    private:
        static bool isLoadingProcessRejected(void);
};


#endif // JVEPROJECT_H


