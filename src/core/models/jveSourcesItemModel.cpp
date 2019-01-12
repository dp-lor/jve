

#include "jveSourcesItemModel.h"


jveSourcesItemModel::jveSourcesItemModel(
          jveApplication *app,
          QDomElement     domNode,
    const int             type
) : jveBaseModel(app, domNode),
        mp_resourcesStructList(),
        mp_streams(),
        mp_id(domNode.attribute("id")),
        mp_checkSum(domNode.attribute("checkSum")),
        mp_type(type)
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

QVector<jveSourceStream *>
jveSourcesItemModel::streams(void) const
{
    return mp_streams;
}

QString
jveSourcesItemModel::id(void) const
{
    return mp_id;
}

QString
jveSourcesItemModel::checkSum(void) const
{
    return mp_checkSum;
}

int
jveSourcesItemModel::type(void) const
{
    return mp_type;
}

int
jveSourcesItemModel::status(void) const
{
    return mp_status;
}

jveSourcesItemStruct
jveSourcesItemModel::itemStruct(void) const
{
    jveSourcesItemStruct itemStruct;

    itemStruct.id           = mp_id;
    itemStruct.type         = mp_type;
    itemStruct.status       = mp_status;
    itemStruct.absolutePath = mp_absolutePath;
    itemStruct.name         = mp_name;
    itemStruct.baseName     = mp_baseName;

    return itemStruct;
}

void
jveSourcesItemModel::setId(const QString &id)
{
    mp_id = id;
    mp_domNode.setAttribute("id", mp_id);
}

void
jveSourcesItemModel::setCheckSum(const QString &checkSum)
{
    mp_checkSum = checkSum;
    mp_domNode.setAttribute("checkSum", mp_checkSum);
}


