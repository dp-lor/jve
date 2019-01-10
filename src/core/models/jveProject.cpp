

#include "jveProject.h"


#include "jveProjectSettings.h"
#include "jveProjectState.h"
#include "jveProjectSources.h"
//#include "jveProjectTree.h"


jveProject::jveProject(jveApplication *app, QDomElement domNode)
    : jveBaseModel(app, domNode),
        // settings
        mp_settings(
            new jveProjectSettings(
                app,
                mp_domNode.firstChildElement("settings")
            )
        ),
        // state
        mp_state(
            new jveProjectState(
                app,
                mp_domNode.firstChildElement("state")
            )
        ),
        // sources
        mp_sources(
            new jveProjectSources(
                app,
                mp_domNode.firstChildElement("sources")
            )
        )/*,
        // tree
        mp_tree(
            new jveProjectTree(
                app,
                mp_domNode.firstChildElement("tree")
            )
        )*/
{
    attachChild(mp_settings);
    attachChild(mp_state);
    attachChild(mp_sources);
    //attachChild(mp_tree);
}

jveProject::~jveProject(void)
{
    clear();
}

void
jveProject::setUp(void)
{
    mp_settings ->setUp();
    mp_state    ->setUp();
    mp_sources  ->setUp();
    //mp_tree     ->setUp();
}


