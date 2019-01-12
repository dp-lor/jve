

#include "jveGuiProjectSourcesViewModel.h"


#include <QIcon>
#include <QMimeData>
#include <QDebug>


#include "../definitions/jveGuiMediaDefines.h"
#include "../../core/signals/jveProjectSourcesSignals.h"


jveGuiProjectSourcesViewModel::jveGuiProjectSourcesViewModel(QObject *parent)
    : QAbstractListModel(parent),
        mp_items(),
        mp_itemToolTip(),
        mp_itemToolTipTypes(jveSourcesItemType::Reserved),
        mp_itemToolTipStatuses(jveSourcesItemStatus::Reserved)
{
    // slot add source item
    connect(
        &jveProjectSourcesSignals,
        SIGNAL(itemAdded(jveSourcesItemStruct)),
        this,
        SLOT(slotAddSourceItem(jveSourcesItemStruct)),
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
            return mp_items.at(row).searchHaystack;
        break;
        case Qt::DisplayRole:
            return mp_items.at(row).displayName;
        break;
        case Qt::DecorationRole:
            return QIcon(JVE_GUI_IMAGE_GRAY_SHARPEN_LOGO);
        break;
        case Qt::ToolTipRole:
            return mp_itemToolTip
                    .arg(mp_itemToolTipTypes.at(mp_items.at(row).type))
                    .arg(mp_items.at(row).absolutePath)
                    .arg(mp_itemToolTipStatuses.at(mp_items.at(row).status));
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

            jveSourcesItemStruct item = mp_items.at(index.row());

            stream
                << item.type
                << item.absolutePath
                << item.displayName
                << item.searchHaystack;

        }
    }
    mimeData->setData("application/jve-project-sources-items", data);

    return mimeData;
}

void
jveGuiProjectSourcesViewModel::updateTranslations(void)
{
    // tool tip placeholder
    mp_itemToolTip = tr("gui_project_sources_view_model_item_tool_tip%1%2%3");

    // undefined item type
    mp_itemToolTipTypes.replace(
        jveSourcesItemType::Undefined,
        tr("gui_project_sources_view_model_item_type_undefined")
    );
    // image item type
    mp_itemToolTipTypes.replace(
        jveSourcesItemType::Image,
        tr("gui_project_sources_view_model_item_type_image")
    );
    // images sequence item type
    mp_itemToolTipTypes.replace(
        jveSourcesItemType::ImagesSequence,
        tr("gui_project_sources_view_model_item_type_images_sequence")
    );
    // audio item type
    mp_itemToolTipTypes.replace(
        jveSourcesItemType::Audio,
        tr("gui_project_sources_view_model_item_type_audio")
    );
    // video item type
    mp_itemToolTipTypes.replace(
        jveSourcesItemType::Video,
        tr("gui_project_sources_view_model_item_type_video")
    );

    // item status ok
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::Ok,
        tr("gui_project_sources_view_model_item_status_ok")
    );
    // resource not exists
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::ResourceNotExists,
        tr("gui_project_sources_view_model_item_status_resource_not_exists")
    );
    // resource not a file
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::ResourceNotFile,
        tr("gui_project_sources_view_model_item_status_resource_not_file")
    );
    // resource not readable
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::ResourceNotReadable,
        tr("gui_project_sources_view_model_item_status_resource_not_readable")
    );
    // error read resource
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::ErrorReadResource,
        tr("gui_project_sources_view_model_item_status_error_read_resource")
    );
    // resource replaced
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::ResourceReplaced,
        tr("gui_project_sources_view_model_item_status_resource_replaced")
    );
    // empty resources list
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::EmptyResourcesList,
        tr("gui_project_sources_view_model_item_status_empty_resources_list")
    );
    // several resources not exists
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::SeveralResourcesNotExists,
        tr("gui_project_sources_view_model_item_status_several_resources_not_exists")
    );
    // several resources not a file
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::SeveralResourcesNotFile,
        tr("gui_project_sources_view_model_item_status_several_resources_not_file")
    );
    // several resources not readable
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::SeveralResourcesNotReadable,
        tr("gui_project_sources_view_model_item_status_several_resources_not_readable")
    );
    // error read several resources
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::ErrorReadSeveralResources,
        tr("gui_project_sources_view_model_item_status_error_read_several_resources")
    );
    // several resources replaced
    mp_itemToolTipStatuses.replace(
        jveSourcesItemStatus::SeveralResourcesReplaced,
        tr("gui_project_sources_view_model_item_status_several_resources_replaced")
    );
}

void
jveGuiProjectSourcesViewModel::slotAddSourceItem(
    const jveSourcesItemStruct &itemStruct
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


