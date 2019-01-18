

#include "JveUndoCommandInfo.h"


JveUndoCommandInfo::JveUndoCommandInfo(const int type)
    : mp_type(type)
{
}

JveUndoCommandInfo::~JveUndoCommandInfo(void)
{
}

int
JveUndoCommandInfo::type(void) const
{
    return mp_type;
}

void
JveUndoCommandInfo::setText(const QString &text)
{
    mp_text = text;
}


