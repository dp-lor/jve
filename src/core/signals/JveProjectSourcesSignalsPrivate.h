

#ifndef JVEPROJECTSOURCESSIGNALSPRIVATE_H
#define JVEPROJECTSOURCESSIGNALSPRIVATE_H


#include <QObject>
#include <QStringList>
#include <QString>


#include "../structures/JveSourcesItemStruct.h"


class JveProjectSourcesSignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  JveProjectSourcesSignalsPrivate(void);
        virtual  ~JveProjectSourcesSignalsPrivate(void);

    signals:

        void wantResetView(void);

        void wantAddItems(const QStringList &itemsList);
        void wantAddImagesSequenceItem(const QStringList &imagesList);

        void wantModifyItem(const JveSourcesItemStruct &itemStruct);
        void wantRemoveItem(const QString &itemId);
        void wantRemoveUnusedItems(void);

        void itemAdded(JveSourcesItemStruct itemStruct);
        void itemRemoved(const QString &itemId);

        void wantShowAddMediaItemsDialog(void);
        void wantShowAddImagesSequenceItemDialog(void);
        void wantShowItemPropertiesDialog(
            const JveSourcesItemStruct &itemStruct
        );
};


#endif // JVEPROJECTSOURCESSIGNALSPRIVATE_H


