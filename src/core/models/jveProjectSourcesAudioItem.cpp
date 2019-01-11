

#include "jveProjectSourcesAudioItem.h"


jveProjectSourcesAudioItem::jveProjectSourcesAudioItem(
    jveApplication *app,
    QDomElement     domNode
) : jveProjectSourcesSingleResourceItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::Audio
    ),
        mp_audioDomElement(domNode.childNodes().at(0).toElement()),
        mp_audioPath(mp_audioDomElement.attribute("path"))
{
    initByResource(mp_audioPath);
}

jveProjectSourcesAudioItem::~jveProjectSourcesAudioItem(void)
{
}


