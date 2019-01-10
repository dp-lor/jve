

#ifndef JVEGUIPROJECTSOURCESVIEWAREA_H
#define JVEGUIPROJECTSOURCESVIEWAREA_H


#include <QListView>
#include <QString>
#include <QPoint>
#include <QSortFilterProxyModel>


#include "jveGuiProjectSourcesViewModel.h"
#include "../menus/jveGuiMenuProjectSources.h"


class jveGuiProjectSourcesViewArea : public QListView
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSourcesViewArea(QWidget *parent);
        virtual  ~jveGuiProjectSourcesViewArea(void);
    public:
        void applyItemsFilter(const QString &needle);
    private slots:
        void slotShowContextMenu(const QPoint &position);
        void slotCatchDoubleClick(const QModelIndex &index);
        void slotDoViewItemProperties(const int targetRow);
        void slotDoRemoveItem(const int targetRow);
    public:
        // members
        jveGuiProjectSourcesViewModel viewModel;
        QSortFilterProxyModel         filterModel;
        jveGuiMenuProjectSources      contextMenu;
};


#endif // JVEGUIPROJECTSOURCESVIEWAREA_H


