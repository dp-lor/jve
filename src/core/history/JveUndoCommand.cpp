

#include "JveUndoCommand.h"


JveUndoCommand::JveUndoCommand(const int type, JveUndoCommand *parent)
    : mp_lockItself(nullptr == parent),
        mp_type(type),
        mp_parent(parent),
        mp_children()
{
    if (nullptr != mp_parent) {
        mp_parent->appendChild(this);
    }
}

JveUndoCommand::~JveUndoCommand(void)
{
    mp_children.clear();
}

int
JveUndoCommand::type(void) const
{
    return mp_type;
}

int
JveUndoCommand::childrenCount(void) const
{
    return mp_children.size();
}

JveUndoCommand *
JveUndoCommand::childAt(const int i)
{
    return mp_children.at(i);
}

void
JveUndoCommand::appendChild(JveUndoCommand *child)
{
    mp_children.append(child);
}

void
JveUndoCommand::undoChildren(void)
{
    for (int i = (mp_children.size() - 1); i > -1; i -= 1) {
        mp_children.at(i)->undoChildren();
        mp_children.at(i)->undo();
    }
}

void
JveUndoCommand::redoChildren(void)
{
    for (int i = 0; i < mp_children.size(); i++) {
        mp_children.at(i)->redo();
        mp_children.at(i)->redoChildren();
    }
}


