

#include "jveProjectSourcesImagesSequenceItem.h"


jveProjectSourcesImagesSequenceItem::jveProjectSourcesImagesSequenceItem(
    jveApplication *app,
    QDomElement     domNode
) : jveProjectSourcesMultipleResourcesItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::ImagesSequence
    ),
        mp_sequenceList()
{
    QDomElement  seqDomElement = domNode.childNodes().at(0).toElement();
    QDomNodeList seqDomNodes   = seqDomElement.childNodes();

    for (int i = 0; i < seqDomNodes.size(); i += 1) {
        mp_sequenceList << seqDomNodes.at(i).toElement().attribute("path");
    }

    initByResources(mp_sequenceList);
}

jveProjectSourcesImagesSequenceItem::~jveProjectSourcesImagesSequenceItem(void)
{
}


