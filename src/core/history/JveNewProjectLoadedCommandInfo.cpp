

#include "JveNewProjectLoadedCommandInfo.h"


JveNewProjectLoadedCommandInfo::JveNewProjectLoadedCommandInfo(void)
    : JveUndoCommandInfo(JveUndoCommandType::NewProjectLoaded)
{
}

JveNewProjectLoadedCommandInfo::~JveNewProjectLoadedCommandInfo(void)
{
}

QString
JveNewProjectLoadedCommandInfo::text(void) const
{
    return mp_text;
}


