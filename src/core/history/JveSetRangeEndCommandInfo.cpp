

#include "JveSetRangeEndCommandInfo.h"


JveSetRangeEndCommandInfo::JveSetRangeEndCommandInfo(
    const int oldRangeEnd,
    const int newRangeEnd
) : JveUndoCommandInfo(JveUndoCommandType::SetRangeEnd),
        mp_oldRangeEnd(oldRangeEnd),
        mp_newRangeEnd(newRangeEnd)
{
}

JveSetRangeEndCommandInfo::~JveSetRangeEndCommandInfo(void)
{
}

QString
JveSetRangeEndCommandInfo::text(void) const
{
    return mp_text.arg(mp_newRangeEnd);
}


