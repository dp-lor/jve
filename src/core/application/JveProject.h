

#ifndef JVEPROJECT_H
#define JVEPROJECT_H


#include <QString>


class JveProject
{
    public:
        static void close(void);
        static void loadNew(void);
        static void load(const QString &filePath);
        static void validateAttributes(void);
        static void validateReferences(void);
        static void initModels(void);
        static void save(const QString &filePath);
    private:
        static bool isLoadingProcessRejected(void);
};


#endif // JVEPROJECT_H


