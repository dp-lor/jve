

#include "jveProjectSourcesItemModel.h"


jveProjectSourcesItemModel::jveProjectSourcesItemModel(
          jveApplication *app,
          QDomElement     domNode,
    const int             type
) : jveBaseModel(app, domNode),
        mp_id(domNode.attribute("id")),
        mp_checkSum(domNode.attribute("checkSum")),
        mp_type(type)
{
}

jveProjectSourcesItemModel::~jveProjectSourcesItemModel(void)
{
}

void
jveProjectSourcesItemModel::setUp(void)
{
}

void
jveProjectSourcesItemModel::upSet(void)
{
}

QString
jveProjectSourcesItemModel::id(void) const
{
    return mp_id;
}

QString
jveProjectSourcesItemModel::checkSum(void) const
{
    return mp_checkSum;
}

int
jveProjectSourcesItemModel::type(void) const
{
    return mp_type;
}

int
jveProjectSourcesItemModel::status(void) const
{
    return mp_status;
}

jveProjectSourcesItemStruct
jveProjectSourcesItemModel::itemStruct(void) const
{
    jveProjectSourcesItemStruct itemStruct;

    itemStruct.id           = mp_id;
    itemStruct.type         = mp_type;
    itemStruct.status       = mp_status;
    itemStruct.absolutePath = mp_absolutePath;
    itemStruct.name         = mp_name;
    itemStruct.baseName     = mp_baseName;

    return itemStruct;
}

void
jveProjectSourcesItemModel::setId(const QString &id)
{
    mp_id = id;
    mp_domNode.setAttribute("id", mp_id);
}

void
jveProjectSourcesItemModel::setCheckSum(const QString &checkSum)
{
    mp_checkSum = checkSum;
    mp_domNode.setAttribute("checkSum", mp_checkSum);
}


