

#ifndef JVESOURCESITEMMODEL_H
#define JVESOURCESITEMMODEL_H


#include "jveBaseModel.h"


#include <QString>


#include "../structures/jveSourcesItemStruct.h"


class jveSourcesItemModel : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveSourcesItemModel(
                  jveApplication *app,
                  QDomElement     domNode,
            const int             type = jveSourcesItemType::Undefined
        );
        virtual ~jveSourcesItemModel(void);
    public:
        void setUp(void);
        void upSet(void);
    public:
        QString id(void) const;
        QString checkSum(void) const;
        int     type(void) const;
        int     status(void) const;
    public:
        jveSourcesItemStruct itemStruct(void) const;
    public:
        void setId(const QString &id);
        void setCheckSum(const QString &checkSum);
    protected:
        // members
        QString mp_id;
        QString mp_checkSum;
        int     mp_type;
        int     mp_status;
        QString mp_absolutePath;
        QString mp_name;
        QString mp_baseName;
};


#endif // JVESOURCESITEMMODEL_H


