

#include "jveVideoItemModel.h"


jveVideoItemModel::jveVideoItemModel(
    jveProject  *project,
    QDomElement  domElement
) : jveSingleResourceItemModel(
        project,
        domElement,
        jveSourcesItemType::Video
    ),
        mp_videoDomElement(mp_domElement.childNodes().at(0).toElement()),
        mp_videoPath(mp_videoDomElement.attribute("path"))
{
    initByResource(mp_videoPath);
}

jveVideoItemModel::~jveVideoItemModel(void)
{
}


