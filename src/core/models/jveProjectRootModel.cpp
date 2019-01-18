

#include "jveProjectRootModel.h"


#include "jveSettingsModel.h"
#include "jveSourcesModel.h"
#include "jveTreeModel.h"
#include "jveStateModel.h"


jveProjectRootModel::jveProjectRootModel(
    jveProject  *project,
    QDomElement  domElement
): jveBaseModel(domElement),
    // settings
    mp_settings(
        new jveSettingsModel(
            project,
            mp_domElement.firstChildElement("settings")
        )
    ),
    // sources
    mp_sources(
        new jveSourcesModel(
            project,
            mp_domElement.firstChildElement("sources")
        )
    ),
    // tree
    mp_tree(
        new jveTreeModel(
            project,
            mp_domElement.firstChildElement("tree")
        )
    ),
    // state
    mp_state(
        new jveStateModel(
            project,
            mp_domElement.firstChildElement("state")
        )
    )
{
    attachChild(mp_settings);
    attachChild(mp_sources);
    attachChild(mp_tree);
    attachChild(mp_state);
}

jveProjectRootModel::~jveProjectRootModel(void)
{
    clear();
}

void
jveProjectRootModel::setUp(void)
{
    mp_settings ->setUp();
    mp_sources  ->setUp();
    mp_tree     ->setUp();
    mp_state    ->setUp();
}


