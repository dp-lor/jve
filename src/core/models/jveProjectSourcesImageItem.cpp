

#include "jveProjectSourcesImageItem.h"


jveProjectSourcesImageItem::jveProjectSourcesImageItem(
    jveApplication *app,
    QDomElement     domNode
) : jveProjectSourcesSingleResourceItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::Image
    ),
        mp_imageDomElement(domNode.childNodes().at(0).toElement()),
        mp_imagePath(mp_imageDomElement.attribute("path"))
{
    initResource(mp_imagePath);
}

jveProjectSourcesImageItem::~jveProjectSourcesImageItem(void)
{
}


