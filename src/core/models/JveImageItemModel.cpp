

#include "JveImageItemModel.h"


JveImageItemModel::JveImageItemModel(
    JveProject  *project,
    QDomElement  domElement
) : JveSingleResourceItemModel(
        project,
        domElement,
        JveSourcesItemType::Image
    ),
        mp_imageDomElement(domElement.childNodes().at(0).toElement()),
        mp_imagePath(mp_imageDomElement.attribute("path"))
{
    initByResource(mp_imagePath);
}

JveImageItemModel::~JveImageItemModel(void)
{
}


