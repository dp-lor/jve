

#include "JveImagesSequenceItemModel.h"


JveImagesSequenceItemModel::JveImagesSequenceItemModel(
    JveProject  *project,
    QDomElement  domElement
) : JveMultipleResourcesItemModel(
        project,
        domElement,
        JveSourcesItemType::ImagesSequence
    ),
        mp_sequenceDomElement(domElement.childNodes().at(0).toElement()),
        mp_sequencePath(mp_sequenceDomElement.attribute("path"))
{
    QDomNodeList sequenceDomNodes = mp_sequenceDomElement.childNodes();

    for (int i = 0; i < sequenceDomNodes.size(); i++) {
        QDomElement itemDomElement = sequenceDomNodes.at(i).toElement();

        mp_sequenceItemsList.append(itemDomElement.attribute("fileName"));
        mp_sequenceItemsDomElements.append(itemDomElement);
    }

    initByResources(mp_sequencePath, mp_sequenceItemsList);

    // check for images only format
    if (JveSourcesItemStatus::Ok == mp_itemStruct.status) {
        foreach (JveSourceResourceStruct resource, mp_itemStruct.resources) {
            if (JveFsFileFormat::Image != resource.format) {
                mp_itemStruct.status
                    = JveSourcesItemStatus::SeveralResourcesNotImage;
                break;
            }
        }
    }
}

JveImagesSequenceItemModel::~JveImagesSequenceItemModel(void)
{
}


