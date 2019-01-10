

#ifndef JVEXMLVALIDATORPRIVATE_H
#define JVEXMLVALIDATORPRIVATE_H


#include <QFile>
#include <QStringList>


class jveXmlValidatorPrivate
{
    public:
        explicit  jveXmlValidatorPrivate(void);
        virtual  ~jveXmlValidatorPrivate(void);
    public:
        void init(void);
        int  validateProjectFile(QFile *projectFile) const;
    private:
        void validateXsdResources(const QStringList *resources);
    private:
        // members
        QStringList mp_xsdProjectSchemas;
};


#endif // JVEXMLVALIDATORPRIVATE_H


