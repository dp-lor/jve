

#ifndef JVEPROJECTSOURCESITEMMODEL_H
#define JVEPROJECTSOURCESITEMMODEL_H


#include "jveBaseModel.h"


#include <QString>


#include "../structures/jveProjectSourcesItemStruct.h"


class jveProjectSourcesItemModel : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveProjectSourcesItemModel(
                  jveApplication *app,
                  QDomElement     domNode,
            const int             type = jveProjectSourcesItemType::Undefined
        );
        virtual ~jveProjectSourcesItemModel(void);
    public:
        void setUp(void);
        void upSet(void);
    public:
        QString id(void) const;
        QString checkSum(void) const;
        int     type(void) const;
        int     status(void) const;
    public:
        jveProjectSourcesItemStruct itemStruct(void) const;
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


#endif // JVEPROJECTSOURCESITEMMODEL_H


