

#ifndef JVEXMLVALIDATORPRIVATE_H
#define JVEXMLVALIDATORPRIVATE_H


#include <QFile>
#include <QStringList>


class JveXmlValidatorPrivate
{
    public:
        explicit  JveXmlValidatorPrivate(void);
        virtual  ~JveXmlValidatorPrivate(void);
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


