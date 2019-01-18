

#include "jveAudioItemModel.h"


jveAudioItemModel::jveAudioItemModel(
    jveProject  *project,
    QDomElement  domElement
) : jveSingleResourceItemModel(
        project,
        domElement,
        jveSourcesItemType::Audio
    ),
        mp_audioDomElement(domElement.childNodes().at(0).toElement()),
        mp_audioPath(mp_audioDomElement.attribute("path"))
{
    initByResource(mp_audioPath);
}

jveAudioItemModel::~jveAudioItemModel(void)
{
}


