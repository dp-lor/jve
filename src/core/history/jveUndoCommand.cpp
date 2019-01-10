

#include "jveUndoCommand.h"


jveUndoCommand::jveUndoCommand(const int type, jveUndoCommand *parent)
    : mp_lockItself(Q_NULLPTR == parent),
        mp_type(type),
        mp_parent(parent),
        mp_children()
{
    if (Q_NULLPTR != mp_parent) {
        mp_parent->appendChild(this);
    }
}

jveUndoCommand::~jveUndoCommand(void)
{
    mp_children.clear();
}

int
jveUndoCommand::type(void) const
{
    return mp_type;
}

int
jveUndoCommand::childrenCount(void) const
{
    return mp_children.size();
}

jveUndoCommand *
jveUndoCommand::childAt(const int i)
{
    return mp_children.at(i);
}

void
jveUndoCommand::appendChild(jveUndoCommand *child)
{
    mp_children.append(child);
}

void
jveUndoCommand::undoChildren(void)
{
    for (int i = (mp_children.size() - 1); i > -1; i -= 1) {
        mp_children.at(i)->undoChildren();
        mp_children.at(i)->undo();
    }
}

void
jveUndoCommand::redoChildren(void)
{
    for (int i = 0; i < mp_children.size(); i += 1) {
        mp_children.at(i)->redo();
        mp_children.at(i)->redoChildren();
    }
}


