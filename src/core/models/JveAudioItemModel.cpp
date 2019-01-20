

#include "JveAudioItemModel.h"


JveAudioItemModel::JveAudioItemModel(
    JveProject  *project,
    QDomElement  domElement
) : JveSingleResourceItemModel(
        project,
        domElement,
        JveSourcesItemType::Audio
    ),
        mp_audioDomElement(domElement.childNodes().at(0).toElement()),
        mp_audioPath(mp_audioDomElement.attribute("path"))
{
    initByResource(mp_audioPath);

    // check for audio only format
    if (
        JveSourcesItemStatus::Ok == mp_itemStruct.status
            && JveFsFileFormat::Audio != mp_itemStruct.resources.at(0).format
    ) {
        mp_itemStruct.status = JveSourcesItemStatus::ResourceNotAudio;
    }
}

JveAudioItemModel::~JveAudioItemModel(void)
{
}


