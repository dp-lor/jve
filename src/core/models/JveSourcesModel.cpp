

#include "JveSourcesModel.h"


#include <QDebug>


#include "JveImageItemModel.h"
#include "JveImagesSequenceItemModel.h"
#include "JveAudioItemModel.h"
#include "JveVideoItemModel.h"

#include "../utils/JveIdProvider.h"
#include "../utils/JveFsUtils.h"
#include "../mutexes/JveProjectMutex.h"

#include "../signals/JveProjectSourcesSignals.h"


JveSourcesModel::JveSourcesModel(QDomElement domElement)
    : JveBaseModel(domElement),
        mp_items()
{
    // items
    QDomNodeList sources = mp_domElement.childNodes();
    for (int i = 0; i < sources.length(); i++) {

        QDomElement siDomElement = sources.at(i).toElement();
        QString     itemType     = siDomElement.childNodes().at(0).nodeName();

        // image
        if ("image" == itemType) {
            attachSourceItem(
                new JveImageItemModel(
                    nullptr,
                    siDomElement,
                    JveSourcesItemOption::ValidateCheckSum
                )
            );
        // images sequence
        } else if ("imagesSequence" == itemType) {
            attachSourceItem(
                new JveImagesSequenceItemModel(
                    nullptr,
                    siDomElement
                )
            );
        // audio
        } else if ("audio" == itemType) {
            attachSourceItem(
                new JveAudioItemModel(
                    nullptr,
                    siDomElement,
                    JveSourcesItemOption::ValidateCheckSum
                )
            );
        // video
        } else if ("video" == itemType) {
            attachSourceItem(
                new JveVideoItemModel(
                    nullptr,
                    siDomElement,
                    JveSourcesItemOption::ValidateCheckSum
                )
            );
        }

    }
}

JveSourcesModel::~JveSourcesModel(void)
{
}

void
JveSourcesModel::setUp(void)
{
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
    // send signals about sources items
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
JveSourcesModel::addItems(const QStringList &resourcesList)
{
    foreach (const QString &resourcePath, resourcesList) {
        switch (JveFsUtils.fileFormat(resourcePath)) {
            // image
            case JveFsFileFormat::Image:
                {
                    JveImageItemModel *item = new JveImageItemModel(
                        nullptr,
                        createSingleResourceItemDom("image", resourcePath),
                        JveSourcesItemOption::None
                    );

                    JveIdProvider.addExternal(item->id());
                    mp_items.insert(item->id(), item);

                    appendChild(item);
                    item->setUp();

                    emit JveProjectSourcesSignals
                            .itemAdded(item->itemStructCopy());
                }
            break;
            // audio
            case JveFsFileFormat::Audio:
                {
                    JveAudioItemModel *item = new JveAudioItemModel(
                        nullptr,
                        createSingleResourceItemDom("audio", resourcePath),
                        JveSourcesItemOption::None
                    );

                    JveIdProvider.addExternal(item->id());
                    mp_items.insert(item->id(), item);

                    appendChild(item);
                    item->setUp();

                    emit JveProjectSourcesSignals
                            .itemAdded(item->itemStructCopy());
                }
            break;
            // video
            case JveFsFileFormat::Video:
                {
                    JveVideoItemModel *item = new JveVideoItemModel(
                        nullptr,
                        createSingleResourceItemDom("video", resourcePath),
                        JveSourcesItemOption::None
                    );

                    JveIdProvider.addExternal(item->id());
                    mp_items.insert(item->id(), item);

                    appendChild(item);
                    item->setUp();

                    emit JveProjectSourcesSignals
                            .itemAdded(item->itemStructCopy());
                }
            break;
            // unsupported
            default:
                continue;
        }
    }
}

void
JveSourcesModel::attachSourceItem(JveSourcesItemModel *item)
{
    JveIdProvider.addExternal(item->id());
    mp_items.insert(item->id(), item);

    attachChild(item);
}

QDomElement
JveSourcesModel::createSingleResourceItemDom(
    const QString &resourceTagName,
    const QString &resourcePath
)
{
    return QDomElement();/*return JveSingleResourceItemModel::createItemDom(
        mp_project->domDocument(),
        resourceTagName,
        mp_project->parentDirPath(),
        resourcePath
    );*/
}

void
JveSourcesModel::slotAddImagesSequenceItem(const QStringList &imagesList)
{
    foreach (const QString &imagePath, imagesList) {
        qDebug() << imagePath;
    }
}


