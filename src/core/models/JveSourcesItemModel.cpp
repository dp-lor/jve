

#include "JveSourcesItemModel.h"


JveSourcesItemModel::JveSourcesItemModel(
          JveProject  *project,
          QDomElement  domElement,
    const int          type
) : JveBaseModel(domElement),
        mp_project(project),
        mp_itemStruct(
            type,
            domElement.attribute("id"),
            domElement.attribute("checkSum")
        ),
        mp_streams()
{
}

JveSourcesItemModel::~JveSourcesItemModel(void)
{
}

void
JveSourcesItemModel::setUp(void)
{
}

void
JveSourcesItemModel::upSet(void)
{
}

QString
JveSourcesItemModel::id(void) const
{
    return mp_itemStruct.id;
}

QString
JveSourcesItemModel::checkSum(void) const
{
    return mp_itemStruct.checkSum;
}

JveSourcesItemStruct
JveSourcesItemModel::itemStructCopy(void)
{
    return JveSourcesItemStruct(mp_itemStruct);
}

void
JveSourcesItemModel::setId(const QString &id)
{
    mp_itemStruct.id = id;
    mp_domElement.setAttribute("id", mp_itemStruct.id);
}

void
JveSourcesItemModel::setCheckSum(const QString &checkSum)
{
    mp_itemStruct.checkSum = checkSum;
    mp_domElement.setAttribute("checkSum", mp_itemStruct.checkSum);
}

QVector<JveSourceStream *>
JveSourcesItemModel::streams(void) const
{
    return mp_streams;
}


