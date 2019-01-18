

#include "jveSourcesModel.h"


#include <QFileInfo>
#include <QDebug>


#include "../application/jveProject.h"

#include "jveImageItemModel.h"
#include "jveImagesSequenceItemModel.h"
#include "jveAudioItemModel.h"
#include "jveVideoItemModel.h"

#include "../utils/jveIdProvider.h"
//#include "../mutexes/jveProjectMutex.h"

#include "../signals/jveProjectSourcesSignals.h"


jveSourcesModel::jveSourcesModel(
    jveProject  *project,
    QDomElement  domElement
) : jveBaseModel(domElement),
        mp_project(project),
        mp_items()
{
    // share self to project
    mp_project->setSourcesModel(this);

    // items
    QDomNodeList sources = mp_domElement.childNodes();
    for (int i = 0; i < sources.length(); i += 1) {

        QDomElement siDomElement = sources.at(i).toElement();
        QString     itemType     = siDomElement.childNodes().at(0).nodeName();

        // image
        if ("image" == itemType) {
            attachSourceItem(new jveImageItemModel(project, siDomElement));
        // images sequence
        } else if ("imagesSequence" == itemType) {
            attachSourceItem(
                new jveImagesSequenceItemModel(
                    project,
                    siDomElement
                )
            );
        // audio
        } else if ("audio" == itemType) {
            attachSourceItem(new jveAudioItemModel(project, siDomElement));
        // video
        } else if ("video" == itemType) {
            attachSourceItem(new jveVideoItemModel(project, siDomElement));
        }

    }
}

jveSourcesModel::~jveSourcesModel(void)
{
}

void
jveSourcesModel::setUp(void)
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
    foreach (jveSourcesItemModel *item, mp_items) {
        emit jveProjectSourcesSignals.itemAdded(item->itemStructCopy());
    }
}

void
jveSourcesModel::upSet(void)
{
    for (int i = 0; i < mp_children.size(); i += 1) {
        mp_children.at(i)->upSet();
    }

    emit jveProjectSourcesSignals.wantResetView();
}

void
jveSourcesModel::attachSourceItem(jveSourcesItemModel *item)
{
    jveIdProvider.addExternal(item->id());
    mp_items.insert(item->id(), item);

    attachChild(item);
}

void
jveSourcesModel::slotAddItems(const QStringList &itemsList)
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
jveSourcesModel::slotAddImagesSequenceItem(const QStringList &imagesList)
{
    foreach (const QString &imagePath, imagesList) {
        qDebug() << imagePath;
    }
}


