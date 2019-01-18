

#include "JveProjectLoadedCommand.h"
#include "JveProjectLoadedCommandInfo.h"


JveProjectLoadedCommand::JveProjectLoadedCommand(void)
    : JveUndoCommand(JveUndoCommandType::ProjectLoaded, nullptr)
{
}

JveProjectLoadedCommand::~JveProjectLoadedCommand(void)
{
}

void
JveProjectLoadedCommand::undo(void)
{
}

void
JveProjectLoadedCommand::redo(void)
{
}

bool
JveProjectLoadedCommand::isEqual(JveUndoCommand *command)
{
    Q_UNUSED(command);

    return false;
}

JveUndoCommandInfo *
JveProjectLoadedCommand::info(void)
{
    return new JveProjectLoadedCommandInfo();
}


