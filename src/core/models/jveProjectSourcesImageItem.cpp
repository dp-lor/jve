

#include "jveProjectSourcesImageItem.h"


jveProjectSourcesImageItem::jveProjectSourcesImageItem(
    jveApplication *app,
    QDomElement     domNode
) : jveProjectSourcesItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::Image
    ),
        mp_imageDomElement(domNode.childNodes().at(0).toElement()),
        mp_imagePath(mp_imageDomElement.attribute("path"))
{
    initEnvironmentBySingleSourceFile(mp_imagePath);
}

jveProjectSourcesImageItem::~jveProjectSourcesImageItem(void)
{
}


