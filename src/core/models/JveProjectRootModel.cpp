

#include "JveProjectRootModel.h"


#include "JveSettingsModel.h"
#include "JveSourcesModel.h"
#include "JveTreeModel.h"
#include "JveStateModel.h"


JveProjectRootModel::JveProjectRootModel(
    JveProject  *project,
    QDomElement  domElement
): JveBaseModel(domElement),
    // settings
    mp_settings(
        new JveSettingsModel(
            project,
            mp_domElement.firstChildElement("settings")
        )
    ),
    // sources
    mp_sources(
        new JveSourcesModel(
            project,
            mp_domElement.firstChildElement("sources")
        )
    ),
    // tree
    mp_tree(
        new JveTreeModel(
            project,
            mp_domElement.firstChildElement("tree")
        )
    ),
    // state
    mp_state(
        new JveStateModel(
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

JveProjectRootModel::~JveProjectRootModel(void)
{
    clear();
}

void
JveProjectRootModel::setUp(void)
{
    mp_settings ->setUp();
    mp_sources  ->setUp();
    mp_tree     ->setUp();
    mp_state    ->setUp();
}


