

#include "jveSetRangeStartCommand.h"
#include "jveSetRangeStartCommandInfo.h"

#include "../models/jveSettingsModel.h"


jveSetRangeStartCommand::jveSetRangeStartCommand(
          jveSettingsModel *settingsModel,
    const int               oldRangeStart,
    const int               newRangeStart,
          jveUndoCommand   *parent
) : jveUndoCommand(jveUndoCommandType::SetRangeStart, parent),
        mp_settingsModel(settingsModel),
        mp_oldRangeStart(oldRangeStart),
        mp_newRangeStart(newRangeStart)
{
}

jveSetRangeStartCommand::~jveSetRangeStartCommand(void)
{
}

int
jveSetRangeStartCommand::oldRangeStart(void) const
{
    return mp_oldRangeStart;
}

int
jveSetRangeStartCommand::newRangeStart(void) const
{
    return mp_newRangeStart;
}

void
jveSetRangeStartCommand::undo(void)
{
    mp_settingsModel->setRangeStart(mp_oldRangeStart, mp_lockItself);
}

void
jveSetRangeStartCommand::redo(void)
{
    mp_settingsModel->setRangeStart(mp_newRangeStart, mp_lockItself);
}

bool
jveSetRangeStartCommand::isEqual(jveUndoCommand *command)
{
    jveSetRangeStartCommand *otherCommand
        = static_cast<jveSetRangeStartCommand *>(command);

    if (mp_oldRangeStart != otherCommand->oldRangeStart()) {
        return false;
    }
    if (mp_newRangeStart != otherCommand->newRangeStart()) {
        return false;
    }

    return true;
}

jveUndoCommandInfo *
jveSetRangeStartCommand::info(void)
{
    return new jveSetRangeStartCommandInfo(mp_oldRangeStart, mp_newRangeStart);
}


