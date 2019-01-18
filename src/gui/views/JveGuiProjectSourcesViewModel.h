

#ifndef JVEGUIPROJECTSOURCESVIEWMODEL_H
#define JVEGUIPROJECTSOURCESVIEWMODEL_H


#include <QAbstractListModel>
#include <QVector>


#include "../../core/structures/JveSourcesItemStruct.h"


class QMimeData;


class JveGuiProjectSourcesViewModel : public QAbstractListModel
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSourcesViewModel(QObject *parent);
        virtual  ~JveGuiProjectSourcesViewModel(void);
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
    public:
        void updateTranslations(void);
    private slots:
        void slotAddSourceItem(const JveSourcesItemStruct &itemStruct);
        void slotRemoveSourceItem(const QString &itemId);
    private:
        // members
        QVector<JveSourcesItemStruct> mp_items;
    private:
        // members
        QString          mp_itemToolTip;
        QVector<QString> mp_itemToolTipTypes;
        QVector<QString> mp_itemToolTipStatuses;
};


#endif // JVEGUIPROJECTSOURCESVIEWMODEL_H


