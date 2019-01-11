

#include "jveProjectSourcesAudioItem.h"


jveProjectSourcesAudioItem::jveProjectSourcesAudioItem(
    jveApplication *app,
    QDomElement     domNode
) : jveSingleResourceItemModel(app, domNode, jveSourcesItemType::Audio),
        mp_audioDomElement(domNode.childNodes().at(0).toElement()),
        mp_audioPath(mp_audioDomElement.attribute("path"))
{
    initByResource(mp_audioPath);
}

jveProjectSourcesAudioItem::~jveProjectSourcesAudioItem(void)
{
}


