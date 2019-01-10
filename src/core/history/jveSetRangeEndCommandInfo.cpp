

#include "jveSetRangeEndCommandInfo.h"


jveSetRangeEndCommandInfo::jveSetRangeEndCommandInfo(
    const int oldRangeEnd,
    const int newRangeEnd
) : jveUndoCommandInfo(jveUndoCommandType::SetRangeEnd),
        mp_oldRangeEnd(oldRangeEnd),
        mp_newRangeEnd(newRangeEnd)
{
}

jveSetRangeEndCommandInfo::~jveSetRangeEndCommandInfo(void)
{
}

QString
jveSetRangeEndCommandInfo::text(void) const
{
    return mp_text.arg(mp_newRangeEnd);
}


