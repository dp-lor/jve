

#include "JveRootModel.h"


#include "JveSettingsModel.h"
#include "JveSourcesModel.h"
#include "JveTreeModel.h"
#include "JveStateModel.h"


JveRootModel::JveRootModel(QDomElement domElement)
    : JveBaseModel(domElement),
    // settings
    mp_settings(
        new JveSettingsModel(
            nullptr,
            mp_domElement.firstChildElement("settings")
        )
    ),
    // sources
    mp_sources(
        new JveSourcesModel(
            nullptr,
            mp_domElement.firstChildElement("sources")
        )
    ),
    // tree
    mp_tree(
        new JveTreeModel(
            nullptr,
            mp_domElement.firstChildElement("tree")
        )
    ),
    // state
    mp_state(
        new JveStateModel(
            nullptr,
            mp_domElement.firstChildElement("state")
        )
    )
{
    attachChild(mp_settings);
    attachChild(mp_sources);
    attachChild(mp_tree);
    attachChild(mp_state);
}

JveRootModel::~JveRootModel(void)
{
    clear();
}

JveSettingsModel *
JveRootModel::settingsModel(void)
{
    return mp_settings;
}

JveSourcesModel *
JveRootModel::sourcesModel(void)
{
    return mp_sources;
}

JveTreeModel *
JveRootModel::treeModel(void)
{
    return mp_tree;
}

JveStateModel *
JveRootModel::stateModel(void)
{
    return mp_state;
}

void
JveRootModel::setUp(void)
{
    mp_settings ->setUp();
    mp_sources  ->setUp();
    mp_tree     ->setUp();
    mp_state    ->setUp();
}


