

#include "jveNewProjectLoadedCommand.h"
#include "jveNewProjectLoadedCommandInfo.h"


jveNewProjectLoadedCommand::jveNewProjectLoadedCommand(void)
    : jveUndoCommand(jveUndoCommandType::NewProjectLoaded, Q_NULLPTR)
{
}

jveNewProjectLoadedCommand::~jveNewProjectLoadedCommand(void)
{
}

void
jveNewProjectLoadedCommand::undo(void)
{
}

void
jveNewProjectLoadedCommand::redo(void)
{
}

bool
jveNewProjectLoadedCommand::isEqual(jveUndoCommand *command)
{
    Q_UNUSED(command);

    return false;
}

jveUndoCommandInfo *
jveNewProjectLoadedCommand::info(void)
{
    return new jveNewProjectLoadedCommandInfo();
}


