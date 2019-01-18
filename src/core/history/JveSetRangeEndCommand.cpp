

#include "JveSetRangeEndCommand.h"
#include "JveSetRangeEndCommandInfo.h"

#include "../models/JveSettingsModel.h"


JveSetRangeEndCommand::JveSetRangeEndCommand(
          JveSettingsModel *settingsModel,
    const int               oldRangeEnd,
    const int               newRangeEnd,
          JveUndoCommand   *parent
) : JveUndoCommand(JveUndoCommandType::SetRangeEnd, parent),
        mp_settingsModel(settingsModel),
        mp_oldRangeEnd(oldRangeEnd),
        mp_newRangeEnd(newRangeEnd)
{
}

JveSetRangeEndCommand::~JveSetRangeEndCommand(void)
{
}

int
JveSetRangeEndCommand::oldRangeEnd(void) const
{
    return mp_oldRangeEnd;
}

int
JveSetRangeEndCommand::newRangeEnd(void) const
{
    return mp_newRangeEnd;
}

void
JveSetRangeEndCommand::undo(void)
{
    mp_settingsModel->setRangeEnd(mp_oldRangeEnd, mp_lockItself);
}

void
JveSetRangeEndCommand::redo(void)
{
    mp_settingsModel->setRangeEnd(mp_newRangeEnd, mp_lockItself);
}

bool
JveSetRangeEndCommand::isEqual(JveUndoCommand *command)
{
    JveSetRangeEndCommand *otherCommand
        = static_cast<JveSetRangeEndCommand *>(command);

    if (mp_oldRangeEnd != otherCommand->oldRangeEnd()) {
        return false;
    }
    if (mp_newRangeEnd != otherCommand->newRangeEnd()) {
        return false;
    }

    return true;
}

JveUndoCommandInfo *
JveSetRangeEndCommand::info(void)
{
    return new JveSetRangeEndCommandInfo(mp_oldRangeEnd, mp_newRangeEnd);
}


