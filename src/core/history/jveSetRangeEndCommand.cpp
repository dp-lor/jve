

#include "jveSetRangeEndCommand.h"
#include "jveSetRangeEndCommandInfo.h"

#include "../models/jveProjectSettings.h"


jveSetRangeEndCommand::jveSetRangeEndCommand(
          jveProjectSettings *settings,
    const int                 oldRangeEnd,
    const int                 newRangeEnd,
          jveUndoCommand     *parent
) : jveUndoCommand(jveUndoCommandType::SetRangeEnd, parent),
        mp_settings(settings),
        mp_oldRangeEnd(oldRangeEnd),
        mp_newRangeEnd(newRangeEnd)
{
}

jveSetRangeEndCommand::~jveSetRangeEndCommand(void)
{
}

int
jveSetRangeEndCommand::oldRangeEnd(void) const
{
    return mp_oldRangeEnd;
}

int
jveSetRangeEndCommand::newRangeEnd(void) const
{
    return mp_newRangeEnd;
}

void
jveSetRangeEndCommand::undo(void)
{
    mp_settings->setRangeEnd(mp_oldRangeEnd, mp_lockItself);
}

void
jveSetRangeEndCommand::redo(void)
{
    mp_settings->setRangeEnd(mp_newRangeEnd, mp_lockItself);
}

bool
jveSetRangeEndCommand::isEqual(jveUndoCommand *command)
{
    jveSetRangeEndCommand *otherCommand
        = static_cast<jveSetRangeEndCommand *>(command);

    if (mp_oldRangeEnd != otherCommand->oldRangeEnd()) {
        return false;
    }
    if (mp_newRangeEnd != otherCommand->newRangeEnd()) {
        return false;
    }

    return true;
}

jveUndoCommandInfo *
jveSetRangeEndCommand::info(void)
{
    return new jveSetRangeEndCommandInfo(mp_oldRangeEnd, mp_newRangeEnd);
}


