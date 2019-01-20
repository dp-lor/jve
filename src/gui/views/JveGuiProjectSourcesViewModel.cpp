

#include "JveGuiProjectSourcesViewModel.h"


#include <QIcon>
#include <QMimeData>
#include <QDebug>


#include "../definitions/JveGuiMediaDefines.h"
#include "../../core/signals/JveProjectSourcesSignals.h"


JveGuiProjectSourcesViewModel::JveGuiProjectSourcesViewModel(QObject *parent)
    : QAbstractListModel(parent),
        mp_items(),
        mp_itemToolTip(),
        mp_itemToolTipTypes(JveSourcesItemType::Reserved),
        mp_itemToolTipStatuses(JveSourcesItemStatus::Reserved)
{
    // slot add source item
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(itemAdded(JveSourcesItemStruct)),
        this,
        SLOT(slotAddSourceItem(JveSourcesItemStruct)),
        Qt::QueuedConnection
    );
    // slot remove source item
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(itemRemoved(QString)),
        this,
        SLOT(slotRemoveSourceItem(QString)),
        Qt::QueuedConnection
    );
}

JveGuiProjectSourcesViewModel::~JveGuiProjectSourcesViewModel(void)
{
    clear();
}

void
JveGuiProjectSourcesViewModel::clear(void)
{
    emit beginRemoveRows(QModelIndex(), 0, mp_items.size() - 1);
    mp_items.clear();
    emit endRemoveRows();
}

void
JveGuiProjectSourcesViewModel::doViewItemProperties(const int row)
{
    if (-1 < row && mp_items.size() > row) {
        emit JveProjectSourcesSignals
                .wantShowItemPropertiesDialog(mp_items.at(row));
    }
}

void
JveGuiProjectSourcesViewModel::doRemoveItem(const int row)
{
    if (-1 < row && mp_items.size() > row) {
        emit JveProjectSourcesSignals.wantRemoveItem(mp_items.at(row).id);
    }
}

int
JveGuiProjectSourcesViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return mp_items.size();
}

QVariant
JveGuiProjectSourcesViewModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role) {
        case Qt::UserRole:
            return mp_items.at(row).searchHaystack;
        case Qt::DisplayRole:
            return mp_items.at(row).displayName;
        case Qt::DecorationRole:
            return QIcon(JVE_GUI_IMAGE_GRAY_SHARPEN_LOGO);
        case Qt::ToolTipRole:
            return mp_itemToolTip
                    .arg(mp_itemToolTipTypes.at(mp_items.at(row).type))
                    .arg(mp_items.at(row).absolutePath)
                    .arg(mp_itemToolTipStatuses.at(mp_items.at(row).status));
    }

    return QVariant();
}

Qt::ItemFlags
JveGuiProjectSourcesViewModel::flags(const QModelIndex &index) const
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
JveGuiProjectSourcesViewModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData   *mimeData = new QMimeData;
    QByteArray   data;
    QDataStream  stream(&data, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {

            JveSourcesItemStruct item = mp_items.at(index.row());

            stream
                << item.type
                << item.absolutePath
                << item.displayName
                << item.searchHaystack;

        }
    }
    mimeData->setData("application/Jve-project-sources-items", data);

    return mimeData;
}

void
JveGuiProjectSourcesViewModel::updateTranslations(void)
{
    // tool tip placeholder
    mp_itemToolTip = tr("gui_project_sources_view_model_item_tool_tip%1%2%3");

    // undefined item type
    mp_itemToolTipTypes.replace(
        JveSourcesItemType::Undefined,
        tr("gui_project_sources_view_model_item_type_undefined")
    );
    // image item type
    mp_itemToolTipTypes.replace(
        JveSourcesItemType::Image,
        tr("gui_project_sources_view_model_item_type_image")
    );
    // images sequence item type
    mp_itemToolTipTypes.replace(
        JveSourcesItemType::ImagesSequence,
        tr("gui_project_sources_view_model_item_type_images_sequence")
    );
    // audio item type
    mp_itemToolTipTypes.replace(
        JveSourcesItemType::Audio,
        tr("gui_project_sources_view_model_item_type_audio")
    );
    // video item type
    mp_itemToolTipTypes.replace(
        JveSourcesItemType::Video,
        tr("gui_project_sources_view_model_item_type_video")
    );

    // item status ok
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::Ok,
        tr("gui_project_sources_view_model_item_status_ok")
    );
    // resource not exists
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ResourceNotExists,
        tr("gui_project_sources_view_model_item_status_resource_not_exists")
    );
    // resource not a file
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ResourceNotFile,
        tr("gui_project_sources_view_model_item_status_resource_not_file")
    );
    // resource not readable
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ResourceNotReadable,
        tr("gui_project_sources_view_model_item_status_resource_not_readable")
    );
    // error read resource
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ErrorReadResource,
        tr("gui_project_sources_view_model_item_status_error_read_resource")
    );
    // resource replaced
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ResourceReplaced,
        tr("gui_project_sources_view_model_item_status_resource_replaced")
    );
    // resource is not image
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ResourceNotImage,
        tr("gui_project_sources_view_model_item_status_resource_not_image")
    );
    // resource is not audio
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ResourceNotAudio,
        tr("gui_project_sources_view_model_item_status_resource_not_audio")
    );
    // resource is not video
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ResourceNotVideo,
        tr("gui_project_sources_view_model_item_status_resource_not_video")
    );
    // empty resources list
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::EmptyResourcesList,
        tr("gui_project_sources_view_model_item_status_empty_resources_list")
    );
    // several resources not exists
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::SeveralResourcesNotExists,
        tr("gui_project_sources_view_model_item_status_several_resources_not_exists")
    );
    // several resources not a file
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::SeveralResourcesNotFile,
        tr("gui_project_sources_view_model_item_status_several_resources_not_file")
    );
    // several resources not readable
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::SeveralResourcesNotReadable,
        tr("gui_project_sources_view_model_item_status_several_resources_not_readable")
    );
    // error read several resources
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::ErrorReadSeveralResources,
        tr("gui_project_sources_view_model_item_status_error_read_several_resources")
    );
    // several resources replaced
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::SeveralResourcesReplaced,
        tr("gui_project_sources_view_model_item_status_several_resources_replaced")
    );
    // several resources is not image
    mp_itemToolTipStatuses.replace(
        JveSourcesItemStatus::SeveralResourcesNotImage,
        tr("gui_project_sources_view_model_item_status_several_resources_not_image")
    );
}

void
JveGuiProjectSourcesViewModel::slotAddSourceItem(
    const JveSourcesItemStruct &itemStruct
)
{
    int newSize = mp_items.size();

    emit beginInsertRows(QModelIndex(), newSize, newSize);
    mp_items.append(itemStruct);
    emit endInsertRows();
}

void
JveGuiProjectSourcesViewModel::slotRemoveSourceItem(const QString &itemId)
{
    int i;

    for (i = 0; i < mp_items.size(); i++) {
        if (0 == itemId.compare(mp_items.at(i).id, Qt::CaseSensitive)) {
            break;
        }
    }

    qDebug() << "Removable index:" << i;
}


