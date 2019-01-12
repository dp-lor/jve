

#include "jveProjectSourcesImagesSequenceItem.h"


jveProjectSourcesImagesSequenceItem::jveProjectSourcesImagesSequenceItem(
    jveApplication *app,
    QDomElement     domNode
) : jveMultipleResourcesItemModel(
        app,
        domNode,
        jveSourcesItemType::ImagesSequence
    ),
        mp_sequenceDomElement(domNode.childNodes().at(0).toElement()),
        mp_sequencePath(mp_sequenceDomElement.attribute("path"))
{
    QDomNodeList sequenceDomNodes = mp_sequenceDomElement.childNodes();

    for (int i = 0; i < sequenceDomNodes.size(); i += 1) {
        QDomElement itemDomElement = sequenceDomNodes.at(i).toElement();

        mp_sequenceItemsList.append(itemDomElement.attribute("fileName"));
        mp_sequenceItemsDomElements.append(itemDomElement);
    }

    initByResources(mp_sequencePath, mp_sequenceItemsList);
}

jveProjectSourcesImagesSequenceItem::~jveProjectSourcesImagesSequenceItem(void)
{
}


