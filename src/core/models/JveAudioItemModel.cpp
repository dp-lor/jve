

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
}

JveAudioItemModel::~JveAudioItemModel(void)
{
}


