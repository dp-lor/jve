

#include "JveImageItemModel.h"


JveImageItemModel::JveImageItemModel(
          JveProject  *project,
          QDomElement  domElement,
    const int          options
) : JveSingleResourceItemModel(
        project,
        domElement,
        JveSourcesItemType::Image
    ),
        mp_imageDomElement(domElement.childNodes().at(0).toElement()),
        mp_imagePath(mp_imageDomElement.attribute("path"))
{
    initByResource(mp_imagePath, options);

    // check for image only format
    if (
        JveSourcesItemStatus::Ok == mp_itemStruct.status
            && JveFsFileFormat::Image != mp_itemStruct.resources.at(0).format
    ) {
        mp_itemStruct.status = JveSourcesItemStatus::ResourceNotImage;
    }
}

JveImageItemModel::~JveImageItemModel(void)
{
}


