

#include "JveVideoItemModel.h"


JveVideoItemModel::JveVideoItemModel(
    JveProject  *project,
    QDomElement  domElement
) : JveSingleResourceItemModel(
        project,
        domElement,
        JveSourcesItemType::Video
    ),
        mp_videoDomElement(mp_domElement.childNodes().at(0).toElement()),
        mp_videoPath(mp_videoDomElement.attribute("path"))
{
    initByResource(mp_videoPath);
}

JveVideoItemModel::~JveVideoItemModel(void)
{
}


