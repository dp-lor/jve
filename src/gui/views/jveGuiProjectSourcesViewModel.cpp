

#include "jveGuiProjectSourcesViewModel.h"


#include <QIcon>
#include <QMimeData>
#include <QDebug>


#include "../definitions/jveGuiMediaDefines.h"
#include "../../core/signals/jveProjectSourcesSignals.h"


jveGuiProjectSourcesViewModel::jveGuiProjectSourcesViewModel(QObject *parent)
    : QAbstractListModel(parent),
        mp_items()
{
    // slot add source item
    connect(
        &jveProjectSourcesSignals,
        SIGNAL(itemAdded(jveProjectSourcesItemStruct)),
        this,
        SLOT(slotAddSourceItem(jveProjectSourcesItemStruct)),
        Qt::QueuedConnection
    );
    // slot remove source item
    connect(
        &jveProjectSourcesSignals,
        SIGNAL(itemRemoved(QString)),
        this,
        SLOT(slotRemoveSourceItem(QString)),
        Qt::QueuedConnection
    );
}

jveGuiProjectSourcesViewModel::~jveGuiProjectSourcesViewModel(void)
{
    clear();
}

void
jveGuiProjectSourcesViewModel::clear(void)
{
    emit beginRemoveRows(QModelIndex(), 0, mp_items.size() - 1);
    mp_items.clear();
    emit endRemoveRows();
}

void
jveGuiProjectSourcesViewModel::doViewItemProperties(const int row)
{
    if (-1 < row && mp_items.size() > row) {
        emit jveProjectSourcesSignals
                .wantShowItemPropertiesDialog(mp_items.at(row));
    }
}

void
jveGuiProjectSourcesViewModel::doRemoveItem(const int row)
{
    if (-1 < row && mp_items.size() > row) {
        emit jveProjectSourcesSignals.wantRemoveItem(mp_items.at(row).id);
    }
}

int
jveGuiProjectSourcesViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return mp_items.size();
}

QVariant
jveGuiProjectSourcesViewModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role) {
        case Qt::UserRole:
            return mp_items.at(row).baseName;
        break;
        case Qt::DisplayRole:
            return mp_items.at(row).name;
        break;
        case Qt::DecorationRole:
            return QIcon(JVE_GUI_IMAGE_GRAY_SHARPEN_LOGO);
        break;
        case Qt::ToolTipRole:
            return tr("Type: %1\nLocation: %2")
                    .arg(mp_items.at(row).type)
                    .arg(mp_items.at(row).absolutePath);
        break;
    }

    return QVariant();
}

Qt::ItemFlags
jveGuiProjectSourcesViewModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        return Qt::ItemNeverHasChildren
                        | Qt::ItemIsEnabled
                        | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled;
    } else {
        return  Qt::ItemNeverHasChildren;
    }
}

QMimeData *
jveGuiProjectSourcesViewModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData   *mimeData = new QMimeData;
    QByteArray   data;
    QDataStream  stream(&data, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {

            jveProjectSourcesItemStruct item = mp_items.at(index.row());

            stream
                << item.type
                << item.absolutePath
                << item.name
                << item.baseName;

        }
    }
    mimeData->setData("application/jve-project-sources-items", data);

    return mimeData;
}

void
jveGuiProjectSourcesViewModel::slotAddSourceItem(
    const jveProjectSourcesItemStruct &itemStruct
)
{
    int newSize = mp_items.size();

    emit beginInsertRows(QModelIndex(), newSize, newSize);
    mp_items.append(itemStruct);
    emit endInsertRows();
}

void
jveGuiProjectSourcesViewModel::slotRemoveSourceItem(const QString &itemId)
{
    int i;

    for (i = 0; i < mp_items.size(); i += 1) {
        if (0 == itemId.compare(mp_items.at(i).id, Qt::CaseSensitive)) {
            break;
        }
    }

    qDebug() << "Removable index:" << i;
}


