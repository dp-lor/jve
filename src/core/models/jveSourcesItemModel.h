

#ifndef JVESOURCESITEMMODEL_H
#define JVESOURCESITEMMODEL_H


#include "jveBaseModel.h"


#include <QString>
#include <QVector>


#include "../structures/jveSourcesItemStruct.h"
#include "../structures/jveSourceResourceStruct.h"

#include "../source-streams/jveSourceStream.h"


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
        QVector<jveSourceResourceStruct> resourcesStructList(void) const;
        QVector<jveSourceStream *>       streams(void) const;
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
        QVector<jveSourceResourceStruct> mp_resourcesStructList;
        QVector<jveSourceStream *>       mp_streams;
    protected:
        // members
        int     mp_type;
        int     mp_status;
        QString mp_id;
        QString mp_checkSum;
        QString mp_absolutePath;
        QString mp_displayName;
        QString mp_searchHaystack;
};


#endif // JVESOURCESITEMMODEL_H


