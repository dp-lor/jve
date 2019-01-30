

#include "JvePrivate.h"


#include "../definitions/JveState.h"


JvePrivate Jve;


JvePrivate::JvePrivate(void)
    : mp_state(JveState::None),
        mp_history(),
        mp_projectParentDirPath(),
        mp_projectFilePath(),
        mp_projectFileName(),
        mp_domDocument(),
        mp_rootModel(nullptr),
        mp_settingsModel(nullptr),
        mp_sourcesModel(nullptr),
        mp_treeModel(nullptr),
        mp_stateModel(nullptr)
{
}

JvePrivate::~JvePrivate(void)
{
}

JveHistory &
JvePrivate::history(void)
{
    return mp_history;
}


