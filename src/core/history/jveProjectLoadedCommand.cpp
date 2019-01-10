

#include "jveProjectLoadedCommand.h"
#include "jveProjectLoadedCommandInfo.h"


jveProjectLoadedCommand::jveProjectLoadedCommand(void)
    : jveUndoCommand(jveUndoCommandType::ProjectLoaded, Q_NULLPTR)
{
}

jveProjectLoadedCommand::~jveProjectLoadedCommand(void)
{
}

void
jveProjectLoadedCommand::undo(void)
{
}

void
jveProjectLoadedCommand::redo(void)
{
}

bool
jveProjectLoadedCommand::isEqual(jveUndoCommand *command)
{
    Q_UNUSED(command);

    return false;
}

jveUndoCommandInfo *
jveProjectLoadedCommand::info(void)
{
    return new jveProjectLoadedCommandInfo();
}


