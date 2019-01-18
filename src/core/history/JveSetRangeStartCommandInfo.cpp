

#include "JveSetRangeStartCommandInfo.h"


JveSetRangeStartCommandInfo::JveSetRangeStartCommandInfo(
    const int oldRangeStart,
    const int newRangeStart
) : JveUndoCommandInfo(JveUndoCommandType::SetRangeStart),
        mp_oldRangeStart(oldRangeStart),
        mp_newRangeStart(newRangeStart)
{
}

JveSetRangeStartCommandInfo::~JveSetRangeStartCommandInfo(void)
{
}

QString
JveSetRangeStartCommandInfo::text(void) const
{
    return mp_text.arg(mp_newRangeStart);
}


