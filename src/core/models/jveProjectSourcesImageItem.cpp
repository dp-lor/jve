

#include "jveProjectSourcesImageItem.h"


jveProjectSourcesImageItem::jveProjectSourcesImageItem(
    jveApplication *app,
    QDomElement     domNode
) : jveSingleResourceItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::Image
    ),
        mp_imageDomElement(domNode.childNodes().at(0).toElement()),
        mp_imagePath(mp_imageDomElement.attribute("path"))
{
    initByResource(mp_imagePath);
}

jveProjectSourcesImageItem::~jveProjectSourcesImageItem(void)
{
}


