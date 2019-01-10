

#include "jveProjectLoadedCommandInfo.h"


jveProjectLoadedCommandInfo::jveProjectLoadedCommandInfo(void)
    : jveUndoCommandInfo(jveUndoCommandType::ProjectLoaded)
{
}

jveProjectLoadedCommandInfo::~jveProjectLoadedCommandInfo(void)
{
}

QString
jveProjectLoadedCommandInfo::text(void) const
{
    return mp_text;
}


