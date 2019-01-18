

#include "JveNewProjectLoadedCommand.h"
#include "JveNewProjectLoadedCommandInfo.h"


JveNewProjectLoadedCommand::JveNewProjectLoadedCommand(void)
    : JveUndoCommand(JveUndoCommandType::NewProjectLoaded, nullptr)
{
}

JveNewProjectLoadedCommand::~JveNewProjectLoadedCommand(void)
{
}

void
JveNewProjectLoadedCommand::undo(void)
{
}

void
JveNewProjectLoadedCommand::redo(void)
{
}

bool
JveNewProjectLoadedCommand::isEqual(JveUndoCommand *command)
{
    Q_UNUSED(command);

    return false;
}

JveUndoCommandInfo *
JveNewProjectLoadedCommand::info(void)
{
    return new JveNewProjectLoadedCommandInfo();
}


