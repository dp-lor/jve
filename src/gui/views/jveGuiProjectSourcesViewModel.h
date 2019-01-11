

#ifndef JVEGUIPROJECTSOURCESVIEWMODEL_H
#define JVEGUIPROJECTSOURCESVIEWMODEL_H


#include <QAbstractListModel>


#include "../../core/structures/jveSourcesItemStruct.h"


class QMimeData;


class jveGuiProjectSourcesViewModel : public QAbstractListModel
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSourcesViewModel(QObject *parent);
        virtual  ~jveGuiProjectSourcesViewModel(void);
    public:
        void clear(void);
    public:
        void doViewItemProperties(const int row);
        void doRemoveItem(const int row);
    public:
        int      rowCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
    public:
        Qt::ItemFlags   flags(const QModelIndex &index) const;
        QMimeData     * mimeData(const QModelIndexList &indexes) const;
    private slots:
        void slotAddSourceItem(const jveSourcesItemStruct &itemStruct);
        void slotRemoveSourceItem(const QString &itemId);
    private:
        // members
        QVector<jveSourcesItemStruct> mp_items;
};


#endif // JVEGUIPROJECTSOURCESVIEWMODEL_H


