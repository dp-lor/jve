

#include "jveSourcesItemModel.h"


jveSourcesItemModel::jveSourcesItemModel(
          jveProject  *project,
          QDomElement  domElement,
    const int          type
) : jveBaseModel(domElement),
        mp_project(project),
        mp_itemStruct(
            type,
            domElement.attribute("id"),
            domElement.attribute("checkSum")
        ),
        mp_streams()
{
}

jveSourcesItemModel::~jveSourcesItemModel(void)
{
}

void
jveSourcesItemModel::setUp(void)
{
}

void
jveSourcesItemModel::upSet(void)
{
}

QString
jveSourcesItemModel::id(void) const
{
    return mp_itemStruct.id;
}

QString
jveSourcesItemModel::checkSum(void) const
{
    return mp_itemStruct.checkSum;
}

jveSourcesItemStruct
jveSourcesItemModel::itemStructCopy(void)
{
    return jveSourcesItemStruct(mp_itemStruct);
}

void
jveSourcesItemModel::setId(const QString &id)
{
    mp_itemStruct.id = id;
    mp_domElement.setAttribute("id", mp_itemStruct.id);
}

void
jveSourcesItemModel::setCheckSum(const QString &checkSum)
{
    mp_itemStruct.checkSum = checkSum;
    mp_domElement.setAttribute("checkSum", mp_itemStruct.checkSum);
}

QVector<jveSourceStream *>
jveSourcesItemModel::streams(void) const
{
    return mp_streams;
}


