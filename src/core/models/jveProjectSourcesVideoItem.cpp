

#include "jveProjectSourcesVideoItem.h"


jveProjectSourcesVideoItem::jveProjectSourcesVideoItem(
    jveApplication *app,
    QDomElement     domNode
) : jveProjectSourcesSingleResourceItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::Video
    ),
        mp_videoDomElement(mp_domNode.childNodes().at(0).toElement()),
        mp_videoPath(mp_videoDomElement.attribute("path"))
{
    initByResource(mp_videoPath);
}

jveProjectSourcesVideoItem::~jveProjectSourcesVideoItem(void)
{
}


