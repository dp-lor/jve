

#include "jveTreeModel.h"


jveTreeModel::jveTreeModel(jveProject *project, QDomElement domElement)
    : jveBaseModel(domElement),
        mp_project(project)
{
}

jveTreeModel::~jveTreeModel(void)
{
}


