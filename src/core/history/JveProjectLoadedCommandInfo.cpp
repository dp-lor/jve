

#include "JveProjectLoadedCommandInfo.h"


JveProjectLoadedCommandInfo::JveProjectLoadedCommandInfo(void)
    : JveUndoCommandInfo(JveUndoCommandType::ProjectLoaded)
{
}

JveProjectLoadedCommandInfo::~JveProjectLoadedCommandInfo(void)
{
}

QString
JveProjectLoadedCommandInfo::text(void) const
{
    return mp_text;
}


