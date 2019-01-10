

#ifndef JVEPROJECTSOURCESSIGNALSPRIVATE_H
#define JVEPROJECTSOURCESSIGNALSPRIVATE_H


#include <QObject>
#include <QStringList>
#include <QString>


#include "../structures/jveProjectSourcesItemStruct.h"


class jveProjectSourcesSignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  jveProjectSourcesSignalsPrivate(void);
        virtual  ~jveProjectSourcesSignalsPrivate(void);

    signals:

        void wantResetView(void);

        void wantAddItems(const QStringList &itemsList);
        void wantAddImagesSequenceItem(const QStringList &imagesList);

        void wantModifyItem(const jveProjectSourcesItemStruct &itemStruct);
        void wantRemoveItem(const QString &itemId);
        void wantRemoveUnusedItems(void);

        void itemAdded(const jveProjectSourcesItemStruct &itemStruct);
        void itemRemoved(const QString &itemId);

        void wantShowAddMediaItemsDialog(void);
        void wantShowAddImagesSequenceItemDialog(void);
        void wantShowItemPropertiesDialog(
            const jveProjectSourcesItemStruct &itemStruct
        );
};


#endif // JVEPROJECTSOURCESSIGNALSPRIVATE_H


