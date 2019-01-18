

#include "jveImageItemModel.h"


jveImageItemModel::jveImageItemModel(
    jveProject  *project,
    QDomElement  domElement
) : jveSingleResourceItemModel(
        project,
        domElement,
        jveSourcesItemType::Image
    ),
        mp_imageDomElement(domElement.childNodes().at(0).toElement()),
        mp_imagePath(mp_imageDomElement.attribute("path"))
{
    initByResource(mp_imagePath);
}

jveImageItemModel::~jveImageItemModel(void)
{
}


