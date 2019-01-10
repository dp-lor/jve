

#include "jveNewProjectLoadedCommandInfo.h"


jveNewProjectLoadedCommandInfo::jveNewProjectLoadedCommandInfo(void)
    : jveUndoCommandInfo(jveUndoCommandType::NewProjectLoaded)
{
}

jveNewProjectLoadedCommandInfo::~jveNewProjectLoadedCommandInfo(void)
{
}

QString
jveNewProjectLoadedCommandInfo::text(void) const
{
    return mp_text;
}


