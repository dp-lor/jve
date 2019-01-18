

#include "JveSourcesModel.h"


#include <QFileInfo>
#include <QDebug>


#include "../application/JveProject.h"

#include "JveImageItemModel.h"
#include "JveImagesSequenceItemModel.h"
#include "JveAudioItemModel.h"
#include "JveVideoItemModel.h"

#include "../utils/JveIdProvider.h"
//#include "../mutexes/JveProjectMutex.h"

#include "../signals/JveProjectSourcesSignals.h"


JveSourcesModel::JveSourcesModel(
    JveProject  *project,
    QDomElement  domElement
) : JveBaseModel(domElement),
        mp_project(project),
        mp_items()
{
    // share self to project
    mp_project->setSourcesModel(this);

    // items
    QDomNodeList sources = mp_domElement.childNodes();
    for (int i = 0; i < sources.length(); i++) {

        QDomElement siDomElement = sources.at(i).toElement();
        QString     itemType     = siDomElement.childNodes().at(0).nodeName();

        // image
        if ("image" == itemType) {
            attachSourceItem(new JveImageItemModel(project, siDomElement));
        // images sequence
        } else if ("imagesSequence" == itemType) {
            attachSourceItem(
                new JveImagesSequenceItemModel(
                    project,
                    siDomElement
                )
            );
        // audio
        } else if ("audio" == itemType) {
            attachSourceItem(new JveAudioItemModel(project, siDomElement));
        // video
        } else if ("video" == itemType) {
            attachSourceItem(new JveVideoItemModel(project, siDomElement));
        }

    }
}

JveSourcesModel::~JveSourcesModel(void)
{
}

void
JveSourcesModel::setUp(void)
{
    // slot add items
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(wantAddItems(QStringList)),
        this,
        SLOT(slotAddItems(QStringList)),
        Qt::QueuedConnection
    );
    // slot add images sequence item
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(wantAddImagesSequenceItem(QStringList)),
        this,
        SLOT(slotAddImagesSequenceItem(QStringList)),
        Qt::QueuedConnection
    );

    // set up children
    for (int i = 0; i < mp_children.size(); i++) {
        mp_children.at(i)->setUp();
    }
    // send signals about all exists sources items
    foreach (JveSourcesItemModel *item, mp_items) {
        emit JveProjectSourcesSignals.itemAdded(item->itemStructCopy());
    }
}

void
JveSourcesModel::upSet(void)
{
    for (int i = 0; i < mp_children.size(); i++) {
        mp_children.at(i)->upSet();
    }

    emit JveProjectSourcesSignals.wantResetView();
}

void
JveSourcesModel::attachSourceItem(JveSourcesItemModel *item)
{
    JveIdProvider.addExternal(item->id());
    mp_items.insert(item->id(), item);

    attachChild(item);
}

void
JveSourcesModel::slotAddItems(const QStringList &itemsList)
{
    QFileInfo info;

    foreach (const QString &itemPath, itemsList) {

        JveSourcesItemStruct itemStruct;

        info.setFile(itemPath);

        itemStruct.type           = 0;
        itemStruct.status         = 0;
        itemStruct.id             = JveIdProvider.generate();
        itemStruct.absolutePath   = info.filePath();
        itemStruct.displayName    = info.fileName();
        itemStruct.searchHaystack = info.baseName();

        JveIdProvider.addExternal(itemStruct.id);

        emit JveProjectSourcesSignals.itemAdded(itemStruct);
    }
}

void
JveSourcesModel::slotAddImagesSequenceItem(const QStringList &imagesList)
{
    foreach (const QString &imagePath, imagesList) {
        qDebug() << imagePath;
    }
}


