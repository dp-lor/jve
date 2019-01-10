

#include "jveProjectSourcesVideoItem.h"


#include <QDebug>


#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"

#include "../application/jveApplication.h"
#include "../utils/jveFsUtils.h"


jveProjectSourcesVideoItem::jveProjectSourcesVideoItem(
    jveApplication *app,
    QDomElement     domNode
) : jveProjectSourcesItemModel(
        app,
        domNode,
        jveProjectSourcesItemType::Video
    ),
        mp_videoDomElement(mp_domNode.childNodes().at(0).toElement()),
        mp_videoPath(mp_videoDomElement.attribute("path"))
        //, mp_avItem()
{
    initEnvironmentBySingleSourceFile(mp_videoPath);


    /*mp_videoFilePath = jveFsUtils.absolutePathOverDirectory(
        mp_app->projectDirPath(),
        mp_videoDomElement.attribute("path")
    );

    // filesystem status
    int mp_fsStatus = jveFsUtils.checkFile(
        mp_videoFilePath,
        jveFsCheckOption::IsExists | jveFsCheckOption::IsReadable
    );

    if (jveFsCheckStatus::Ok == mp_fsStatus) {
        //mp_avItem.open(mp_videoFilePath);
    }*/
}

jveProjectSourcesVideoItem::~jveProjectSourcesVideoItem(void)
{
}


