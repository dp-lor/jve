

#include "jveProjectSourcesVideoItem.h"


jveProjectSourcesVideoItem::jveProjectSourcesVideoItem(
    jveApplication *app,
    QDomElement     domNode
) : jveSingleResourceItemModel(app, domNode, jveSourcesItemType::Video),
        mp_videoDomElement(mp_domNode.childNodes().at(0).toElement()),
        mp_videoPath(mp_videoDomElement.attribute("path"))
{
    initByResource(mp_videoPath);
}

jveProjectSourcesVideoItem::~jveProjectSourcesVideoItem(void)
{
}


