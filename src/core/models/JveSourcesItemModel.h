

#ifndef JVESOURCESITEMMODEL_H
#define JVESOURCESITEMMODEL_H


#include "JveBaseModel.h"


#include "../structures/JveSourcesItemStruct.h"
#include "../source-streams/JveSourceStream.h"


class JveProject;


class JveSourcesItemModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit JveSourcesItemModel(
                  JveProject  *project,
                  QDomElement  domElement,
            const int          type
        );
        virtual ~JveSourcesItemModel(void);
    public:
        void setUp(void);
        void upSet(void);
    public:
        QString id(void) const;
        QString checkSum(void) const;
    public:
        int status(void) const;
    public:
        JveSourcesItemStruct itemStructCopy(void);
    public:
        void setId(const QString &id);
        void setCheckSum(const QString &checkSum);
    public:
        QVector<JveSourceStream *> streams(void) const;
    protected:
        // members
        JveProject                 *mp_project;
        JveSourcesItemStruct        mp_itemStruct;
        QVector<JveSourceStream *>  mp_streams;
};


#endif // JVESOURCESITEMMODEL_H


