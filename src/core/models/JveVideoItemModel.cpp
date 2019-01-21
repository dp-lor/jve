

#include "JveVideoItemModel.h"


JveVideoItemModel::JveVideoItemModel(
          JveProject  *project,
          QDomElement  domElement,
    const int          options
) : JveSingleResourceItemModel(
        project,
        domElement,
        JveSourcesItemType::Video
    ),
        mp_videoDomElement(mp_domElement.childNodes().at(0).toElement()),
        mp_videoPath(mp_videoDomElement.attribute("path"))
{
    initByResource(mp_videoPath, options);

    // check for video only format
    if (
        JveSourcesItemStatus::Ok == mp_itemStruct.status
            && JveFsFileFormat::Video != mp_itemStruct.resources.at(0).format
    ) {
        mp_itemStruct.status = JveSourcesItemStatus::ResourceNotVideo;
    }
}

JveVideoItemModel::~JveVideoItemModel(void)
{
}


