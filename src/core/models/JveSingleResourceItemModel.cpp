

#include "JveSingleResourceItemModel.h"


#include <QFile>
#include <QCryptographicHash>


#include "../definitions/JveFsCheckOption.h"
#include "../definitions/JveFsCheckStatus.h"

#include "../application/JveProject.h"

#include "../utils/JveIdProvider.h"
#include "../utils/JveFsUtils.h"


JveSingleResourceItemModel::JveSingleResourceItemModel(
              JveProject  *project,
              QDomElement  domElement,
        const int          type
    ) : JveSourcesItemModel(project, domElement, type)
{
}

JveSingleResourceItemModel::~JveSingleResourceItemModel(void)
{
}

QDomElement
JveSingleResourceItemModel::createItemDom(
          QDomDocument &domDocument,
    const QString      &resourceTagName,
    const QString      &projectParentDirPath,
    const QString      &resourcePath
)
{
    QDomElement itemDomEl     = domDocument.createElement("sourceItem");
    QDomElement resourceDomEl = domDocument.createElement(resourceTagName);

    QFile              checkSumFile(resourcePath);
    QCryptographicHash checkSumHash(QCryptographicHash::Md5);
    QString            checkSum("none");

    // create checksum
    if (checkSumFile.open(QFile::ReadOnly)) {
        checkSumHash.addData(&checkSumFile);
        checkSum = checkSumHash.result().toHex();
    }

    // set item element attributes
    itemDomEl.setAttribute("id", JveIdProvider.generate());
    itemDomEl.setAttribute("checkSum", checkSum);
    // set resource attribute
    resourceDomEl.setAttribute(
        "path",
        JveFsUtils.relativePathOverDirectory(
            projectParentDirPath,
            resourcePath
        )
    );
    // append resource to item
    itemDomEl.appendChild(resourceDomEl);

    return itemDomEl;
}

void
JveSingleResourceItemModel::initByResource(
    const QString &resourcePath,
    const int      options
)
{
    // absolute path
    mp_itemStruct.absolutePath = JveFsUtils.absolutePathOverDirectory(
        mp_project->parentDirPath(),
        resourcePath
    );
    // display name
    mp_itemStruct.displayName = JveFsUtils.name(mp_itemStruct.absolutePath);
    // base name
    mp_itemStruct.baseName = JveFsUtils.baseName(mp_itemStruct.absolutePath);
    if (0 == mp_itemStruct.baseName.size()) {
        mp_itemStruct.baseName = mp_itemStruct.displayName;
    }
    // search haystack
    mp_itemStruct.searchHaystack = mp_itemStruct.baseName;

    // fill resource struct
    JveSourceResourceStruct resourceStruct(
        mp_itemStruct.absolutePath,
        JveFsUtils.checkFile(
            mp_itemStruct.absolutePath,
            JveFsCheckOption::IsExists | JveFsCheckOption::IsReadable
        )
    );

    // item status by resource status
    switch (resourceStruct.status) {
        // not exists
        case JveFsCheckStatus::NotExists:
            mp_itemStruct.status = JveSourcesItemStatus::ResourceNotExists;
        break;
        // not a file
        case JveFsCheckStatus::NotFile:
            mp_itemStruct.status = JveSourcesItemStatus::ResourceNotFile;
        break;
        // not readable
        case JveFsCheckStatus::NotReadable:
            mp_itemStruct.status = JveSourcesItemStatus::ResourceNotReadable;
        break;
    }

    if (JveSourcesItemStatus::Ok == mp_itemStruct.status) {

        // detect format
        resourceStruct.format
            = JveFsUtils.fileFormat(resourceStruct.absolutePath);

        if (options & JveSourcesItemOption::ValidateCheckSum) {
            // validate checksum
            QFile checkSumFile(resourceStruct.absolutePath);
            if (checkSumFile.open(QFile::ReadOnly)) {
                QCryptographicHash checkSumHash(QCryptographicHash::Md5);
                checkSumHash.addData(&checkSumFile);
                if (mp_itemStruct.checkSum != checkSumHash.result().toHex()) {
                    mp_itemStruct.status = JveSourcesItemStatus::ResourceReplaced;
                }
                checkSumFile.close();
            } else {
                mp_itemStruct.status = JveSourcesItemStatus::ErrorReadResource;
            }
        }

    }

    // append resource struct to resources list
    mp_itemStruct.resources.append(resourceStruct);
}


