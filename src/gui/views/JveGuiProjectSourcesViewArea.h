

#ifndef JVEGUIPROJECTSOURCESVIEWAREA_H
#define JVEGUIPROJECTSOURCESVIEWAREA_H


#include <QListView>
#include <QString>
#include <QPoint>
#include <QSortFilterProxyModel>


#include "JveGuiProjectSourcesViewModel.h"
#include "../menus/JveGuiMenuProjectSources.h"


class JveGuiProjectSourcesViewArea : public QListView
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSourcesViewArea(QWidget *parent);
        virtual  ~JveGuiProjectSourcesViewArea(void);
    public:
        void applyItemsFilter(const QString &needle);
    private slots:
        void slotShowContextMenu(const QPoint &position);
        void slotCatchDoubleClick(const QModelIndex &index);
        void slotDoViewItemProperties(const int targetRow);
        void slotDoRemoveItem(const int targetRow);
    public:
        // members
        JveGuiProjectSourcesViewModel viewModel;
        QSortFilterProxyModel         filterModel;
        JveGuiMenuProjectSources      contextMenu;
};


#endif // JVEGUIPROJECTSOURCESVIEWAREA_H


