

#include "jveSetRangeStartCommandInfo.h"


jveSetRangeStartCommandInfo::jveSetRangeStartCommandInfo(
    const int oldRangeStart,
    const int newRangeStart
) : jveUndoCommandInfo(jveUndoCommandType::SetRangeStart),
        mp_oldRangeStart(oldRangeStart),
        mp_newRangeStart(newRangeStart)
{
}

jveSetRangeStartCommandInfo::~jveSetRangeStartCommandInfo(void)
{
}

QString
jveSetRangeStartCommandInfo::text(void) const
{
    return mp_text.arg(mp_newRangeStart);
}


