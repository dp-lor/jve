

#include "jveProjectSources.h"


#include <QFileInfo>
#include <QDebug>


#include "jveProjectSourcesImageItem.h"
#include "jveProjectSourcesImagesSequenceItem.h"
#include "jveProjectSourcesAudioItem.h"
#include "jveProjectSourcesVideoItem.h"

#include "../utils/jveIdProvider.h"
//#include "../mutexes/jveProjectMutex.h"
#include "../application/jveApplication.h"

#include "../signals/jveProjectSourcesSignals.h"


jveProjectSources::jveProjectSources(
    jveApplication *app,
    QDomElement     domNode
) : jveBaseModel(app, domNode),
    mp_items()
{
    // share self to application
    mp_app->setProjectSources(this);

    // items
    QDomNodeList sources = mp_domNode.childNodes();
    for (int i = 0; i < sources.length(); i += 1) {

        QDomElement siDomElement = sources.at(i).toElement();
        QString     itemType     = siDomElement.childNodes().at(0).nodeName();

        // image
        if ("image" == itemType) {
            attachSourceItem(
                new jveProjectSourcesImageItem(
                    app,
                    siDomElement
                )
            );
        // images sequence
        } else if ("imagesSequence" == itemType) {
            attachSourceItem(
                new jveProjectSourcesImagesSequenceItem(
                    app,
                    siDomElement
                )
            );
        // audio
        } else if ("audio" == itemType) {
            attachSourceItem(
                new jveProjectSourcesAudioItem(
                    app,
                    siDomElement
                )
            );
        // video
        } else if ("video" == itemType) {
            attachSourceItem(
                new jveProjectSourcesVideoItem(
                    app,
                    siDomElement
                )
            );
        }

    }
}

jveProjectSources::~jveProjectSources(void)
{
}

void
jveProjectSources::setUp(void)
{
    // slot add items
    connect(
        &jveProjectSourcesSignals,
        SIGNAL(wantAddItems(QStringList)),
        this,
        SLOT(slotAddItems(QStringList)),
        Qt::QueuedConnection
    );
    // slot add images sequence item
    connect(
        &jveProjectSourcesSignals,
        SIGNAL(wantAddImagesSequenceItem(QStringList)),
        this,
        SLOT(slotAddImagesSequenceItem(QStringList)),
        Qt::QueuedConnection
    );

    // set up children
    for (int i = 0; i < mp_children.size(); i += 1) {
        mp_children.at(i)->setUp();
    }
    // send signals about all exists sources items
    foreach (const jveSourcesItemModel *item, mp_items) {
        emit jveProjectSourcesSignals.itemAdded(item->itemStruct());
    }
}

void
jveProjectSources::upSet(void)
{
    for (int i = 0; i < mp_children.size(); i += 1) {
        mp_children.at(i)->upSet();
    }

    emit jveProjectSourcesSignals.wantResetView();
}

void
jveProjectSources::attachSourceItem(jveSourcesItemModel *item)
{
    jveIdProvider.addExternal(item->id());
    mp_items.insert(item->id(), item);

    attachChild(item);
}

void
jveProjectSources::slotAddItems(const QStringList &itemsList)
{
    QFileInfo info;

    foreach (const QString &itemPath, itemsList) {

        jveSourcesItemStruct itemStruct;

        info.setFile(itemPath);

        itemStruct.type           = 0;
        itemStruct.status         = 0;
        itemStruct.id             = jveIdProvider.generate();
        itemStruct.absolutePath   = info.filePath();
        itemStruct.displayName    = info.fileName();
        itemStruct.searchHaystack = info.baseName();

        jveIdProvider.addExternal(itemStruct.id);

        emit jveProjectSourcesSignals.itemAdded(itemStruct);
    }
}

void
jveProjectSources::slotAddImagesSequenceItem(const QStringList &imagesList)
{
    foreach (const QString &imagePath, imagesList) {
        qDebug() << imagePath;
    }
}


