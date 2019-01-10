

#include "jveProjectSourcesImagesSequenceItem.h"


jveProjectSourcesImagesSequenceItem::jveProjectSourcesImagesSequenceItem(
    jveApplication *app,
    QDomElement     domNode
) : jveProjectSourcesItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::ImagesSequence
    )
{
    QDomElement  seqDomElement = domNode.childNodes().at(0).toElement();
    QDomNodeList seqDomNodes   = seqDomElement.childNodes();

    for (int i = 0; i < seqDomNodes.size(); i += 1) {
        mp_sequencePaths << seqDomNodes.at(i).toElement().attribute("path");
    }

    initEnvironmentBySourceFilesSequence(mp_sequencePaths);
}

jveProjectSourcesImagesSequenceItem::~jveProjectSourcesImagesSequenceItem(void)
{
}


