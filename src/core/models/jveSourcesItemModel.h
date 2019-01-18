

#ifndef JVESOURCESITEMMODEL_H
#define JVESOURCESITEMMODEL_H


#include "jveBaseModel.h"


#include "../structures/jveSourcesItemStruct.h"
#include "../source-streams/jveSourceStream.h"


class jveProject;


class jveSourcesItemModel : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveSourcesItemModel(
                  jveProject  *project,
                  QDomElement  domElement,
            const int          type
        );
        virtual ~jveSourcesItemModel(void);
    public:
        void setUp(void);
        void upSet(void);
    public:
        QString id(void) const;
        QString checkSum(void) const;
    public:
        jveSourcesItemStruct itemStructCopy(void);
    public:
        void setId(const QString &id);
        void setCheckSum(const QString &checkSum);
    public:
        QVector<jveSourceStream *> streams(void) const;
    protected:
        // members
        jveProject                 *mp_project;
        jveSourcesItemStruct        mp_itemStruct;
        QVector<jveSourceStream *>  mp_streams;
};


#endif // JVESOURCESITEMMODEL_H


