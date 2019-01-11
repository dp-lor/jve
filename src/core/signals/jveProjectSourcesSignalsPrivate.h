

#ifndef JVEPROJECTSOURCESSIGNALSPRIVATE_H
#define JVEPROJECTSOURCESSIGNALSPRIVATE_H


#include <QObject>
#include <QStringList>
#include <QString>


#include "../structures/jveSourcesItemStruct.h"


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

        void wantModifyItem(const jveSourcesItemStruct &itemStruct);
        void wantRemoveItem(const QString &itemId);
        void wantRemoveUnusedItems(void);

        void itemAdded(const jveSourcesItemStruct &itemStruct);
        void itemRemoved(const QString &itemId);

        void wantShowAddMediaItemsDialog(void);
        void wantShowAddImagesSequenceItemDialog(void);
        void wantShowItemPropertiesDialog(
            const jveSourcesItemStruct &itemStruct
        );
};


#endif // JVEPROJECTSOURCESSIGNALSPRIVATE_H


