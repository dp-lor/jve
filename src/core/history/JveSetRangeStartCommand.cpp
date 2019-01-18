

#include "JveSetRangeStartCommand.h"
#include "JveSetRangeStartCommandInfo.h"

#include "../models/JveSettingsModel.h"


JveSetRangeStartCommand::JveSetRangeStartCommand(
          JveSettingsModel *settingsModel,
    const int               oldRangeStart,
    const int               newRangeStart,
          JveUndoCommand   *parent
) : JveUndoCommand(JveUndoCommandType::SetRangeStart, parent),
        mp_settingsModel(settingsModel),
        mp_oldRangeStart(oldRangeStart),
        mp_newRangeStart(newRangeStart)
{
}

JveSetRangeStartCommand::~JveSetRangeStartCommand(void)
{
}

int
JveSetRangeStartCommand::oldRangeStart(void) const
{
    return mp_oldRangeStart;
}

int
JveSetRangeStartCommand::newRangeStart(void) const
{
    return mp_newRangeStart;
}

void
JveSetRangeStartCommand::undo(void)
{
    mp_settingsModel->setRangeStart(mp_oldRangeStart, mp_lockItself);
}

void
JveSetRangeStartCommand::redo(void)
{
    mp_settingsModel->setRangeStart(mp_newRangeStart, mp_lockItself);
}

bool
JveSetRangeStartCommand::isEqual(JveUndoCommand *command)
{
    JveSetRangeStartCommand *otherCommand
        = static_cast<JveSetRangeStartCommand *>(command);

    if (mp_oldRangeStart != otherCommand->oldRangeStart()) {
        return false;
    }
    if (mp_newRangeStart != otherCommand->newRangeStart()) {
        return false;
    }

    return true;
}

JveUndoCommandInfo *
JveSetRangeStartCommand::info(void)
{
    return new JveSetRangeStartCommandInfo(mp_oldRangeStart, mp_newRangeStart);
}


