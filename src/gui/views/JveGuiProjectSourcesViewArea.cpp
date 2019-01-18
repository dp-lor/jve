

#include "JveGuiProjectSourcesViewArea.h"


#include <QDebug>


#include "../../core/signals/JveProjectSourcesSignals.h"


JveGuiProjectSourcesViewArea::JveGuiProjectSourcesViewArea(QWidget *parent)
    : QListView(parent),
        viewModel(this),
        filterModel(this),
        contextMenu(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    setIconSize(QSize(40, 40));
    setWordWrap(false);
    setMovement(QListView::Static);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setDragDropMode(QAbstractItemView::DragOnly);
    setContextMenuPolicy(Qt::CustomContextMenu);

    // model
    filterModel.setSourceModel(&viewModel);
    filterModel.setFilterRole(Qt::UserRole);
    filterModel.setFilterCaseSensitivity(Qt::CaseInsensitive);
    setModel(&filterModel);

    // context menu
    connect(
        this,
        SIGNAL(customContextMenuRequested(QPoint)),
        this,
        SLOT(slotShowContextMenu(QPoint)),
        Qt::DirectConnection
    );

    // double click
    connect(
        this,
        SIGNAL(doubleClicked(QModelIndex)),
        this,
        SLOT(slotCatchDoubleClick(QModelIndex)),
        Qt::DirectConnection
    );

    // view properties
    connect(
        &contextMenu,
        SIGNAL(wantViewItemProperties(int)),
        this,
        SLOT(slotDoViewItemProperties(int)),
        Qt::DirectConnection
    );
    // remove item
    connect(
        &contextMenu,
        SIGNAL(wantRemoveItem(int)),
        this,
        SLOT(slotDoRemoveItem(int)),
        Qt::DirectConnection
    );
}

JveGuiProjectSourcesViewArea::~JveGuiProjectSourcesViewArea(void)
{
}

void
JveGuiProjectSourcesViewArea::applyItemsFilter(const QString &needle)
{
    filterModel.setFilterFixedString(needle);
}

void
JveGuiProjectSourcesViewArea::slotShowContextMenu(const QPoint &position)
{
    QModelIndex index = indexAt(position);

    setCurrentIndex(index);

    contextMenu.setTargetRow(filterModel.mapToSource(index).row());
    contextMenu.exec(viewport()->mapToGlobal(position));
}

void
JveGuiProjectSourcesViewArea::slotCatchDoubleClick(const QModelIndex &index)
{
    contextMenu.setTargetRow(filterModel.mapToSource(index).row());
    contextMenu.actionProperties.trigger();
}

void
JveGuiProjectSourcesViewArea::slotDoViewItemProperties(const int targetRow)
{
    viewModel.doViewItemProperties(targetRow);
}

void
JveGuiProjectSourcesViewArea::slotDoRemoveItem(const int targetRow)
{
    viewModel.doRemoveItem(targetRow);
}


