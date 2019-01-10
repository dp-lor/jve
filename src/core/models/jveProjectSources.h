

#ifndef JVEPROJECTSOURCES_H
#define JVEPROJECTSOURCES_H


#include "jveBaseModel.h"


#include <QHash>
#include <QString>
#include <QStringList>


class jveProjectSourcesItemModel;


class jveProjectSources : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveProjectSources(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveProjectSources(void);
    public:
        void setUp(void);
        void upSet(void);
    private:
        void attachSourceItem(jveProjectSourcesItemModel *item);
    private slots:
        void slotAddItems(const QStringList &itemsList);
        void slotAddImagesSequenceItem(const QStringList &imagesList);
    private:
        // members
        QHash<QString, jveProjectSourcesItemModel *> mp_items;
};


#endif // JVEPROJECTSOURCES_H


