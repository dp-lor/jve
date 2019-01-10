

#include "jveUndoCommandInfo.h"


jveUndoCommandInfo::jveUndoCommandInfo(const int type)
    : mp_type(type)
{
}

jveUndoCommandInfo::~jveUndoCommandInfo(void)
{
}

int
jveUndoCommandInfo::type(void) const
{
    return mp_type;
}

void
jveUndoCommandInfo::setText(const QString &text)
{
    mp_text = text;
}


