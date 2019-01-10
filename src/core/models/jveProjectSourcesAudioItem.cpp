

#include "jveProjectSourcesAudioItem.h"


jveProjectSourcesAudioItem::jveProjectSourcesAudioItem(
    jveApplication *app,
    QDomElement     domNode
) : jveProjectSourcesItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::Audio
    ),
        mp_audioDomElement(domNode.childNodes().at(0).toElement()),
        mp_audioPath(mp_audioDomElement.attribute("path"))
{
    initEnvironmentBySingleSourceFile(mp_audioPath);
}

jveProjectSourcesAudioItem::~jveProjectSourcesAudioItem(void)
{
}


