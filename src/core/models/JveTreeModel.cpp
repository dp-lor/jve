

#include "JveTreeModel.h"


JveTreeModel::JveTreeModel(JveProject *project, QDomElement domElement)
    : JveBaseModel(domElement),
        mp_project(project)
{
}

JveTreeModel::~JveTreeModel(void)
{
}


