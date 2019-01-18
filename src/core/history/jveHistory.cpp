

#include "jveHistory.h"


#include "../signals/jveHistorySignals.h"

#include "../mutexes/jveProjectMutex.h"
#include "../application/jveProject.h"

#include "jveUndoCommand.h"

#include "jveProjectLoadedCommand.h"
#include "jveNewProjectLoadedCommand.h"
#include "jveSetRangeStartCommand.h"
#include "jveSetRangeEndCommand.h"

#include "jveProjectLoadedCommandInfo.h"
#include "jveNewProjectLoadedCommandInfo.h"
#include "jveSetRangeStartCommandInfo.h"
#include "jveSetRangeEndCommandInfo.h"


jveHistory::jveHistory(jveProject *project)
    : QObject(Q_NULLPTR),
        mp_project(project),
        mp_undoStackCurrentIndex(-1),
        mp_undoStackCleanIndex(-1),
        mp_undoStack()
{
    // slot set undo stack current index
    connect(
        &jveHistorySignals,
        SIGNAL(wantSetUndoStackCurrentIndex(int)),
        this,
        SLOT(slotSetUndoStackCurrentIndex(int)),
        Qt::QueuedConnection
    );
}

jveHistory::~jveHistory(void)
{
    mp_undoStack.clear();
}

void
jveHistory::clear(void)
{
    mp_undoStackCurrentIndex = -1;
    mp_undoStackCleanIndex   = -1;

    mp_undoStack.clear();
    emit jveHistorySignals.undoStackChanged(
        mp_undoStack.size(),
        mp_undoStackCurrentIndex,
        mp_undoStackCleanIndex,
        Q_NULLPTR
    );
}

void
jveHistory::setProjectLoadedState(void)
{
    mp_undoStackCleanIndex = 0;
    appendUndoCommandWithModifiedState(
        new jveProjectLoadedCommand(), false);
}

void
jveHistory::setNewProjectLoadedState(void)
{
    mp_undoStackCleanIndex = 0;
    appendUndoCommandWithModifiedState(
        new jveNewProjectLoadedCommand(), false);
}

void
jveHistory::appendUndoCommand(jveUndoCommand *undoCommand)
{
    appendUndoCommandWithModifiedState(undoCommand, true);
}

void
jveHistory::setUndoStackClean(void)
{
    if (mp_undoStackCleanIndex != mp_undoStackCurrentIndex) {
        mp_undoStackCleanIndex = mp_undoStackCurrentIndex;
        mp_project->setModified(false);
        emit jveHistorySignals.undoStackChanged(
            mp_undoStack.size(),
            mp_undoStackCurrentIndex,
            mp_undoStackCleanIndex,
            Q_NULLPTR
        );
    }
}

void
jveHistory::appendUndoCommandWithModifiedState(
          jveUndoCommand *undoCommand,
    const bool            modified
)
{
    jveUndoCommandInfo *undoCommandInfo     = Q_NULLPTR;
    int                 nextCommandIndex    = mp_undoStackCurrentIndex + 1;
    bool                canAppendNewCommand = true;

    // not last index
    if (mp_undoStackCurrentIndex < (mp_undoStack.size() - 1)) {

        jveUndoCommand *nextUndoCommand = mp_undoStack.at(nextCommandIndex);

        // equal (including children, recursively)
        if (isEqualUndoCommands(undoCommand, nextUndoCommand)) {

            // not need append new command
            canAppendNewCommand      = false;
            mp_undoStackCurrentIndex = nextCommandIndex;

            delete undoCommand;

        // different
        } else {

            while (nextCommandIndex < mp_undoStack.size()) {
                mp_undoStack.removeLast();
            }
            if (mp_undoStackCleanIndex > (mp_undoStack.size() - 1)) {
                mp_undoStackCleanIndex = -1;
                mp_project->setModified(modified);
            }

        }

    }

    // append new command
    if (canAppendNewCommand) {

        undoCommand->redo();
        undoCommand->redoChildren();
        mp_undoStack.append(undoCommand);

        mp_undoStackCurrentIndex = nextCommandIndex;
        undoCommandInfo          = undoCommand->info();

        mp_project->setModified(modified);
    }

    // always something changed
    emit jveHistorySignals.undoStackChanged(
        mp_undoStack.size(),
        mp_undoStackCurrentIndex,
        mp_undoStackCleanIndex,
        undoCommandInfo
    );
}

bool
jveHistory::isEqualUndoCommands(
    jveUndoCommand *firstCommand,
    jveUndoCommand *secondCommand
) const
{
    // by type
    if (firstCommand->type() != secondCommand->type()) {
        return false;
    }
    // by children count
    if (firstCommand->childrenCount() != secondCommand->childrenCount()) {
        return false;
    }
    // internal
    if (!(firstCommand->isEqual(secondCommand))) {
        return false;
    }
    // child with child (recursively)
    for (int i = 0; i < firstCommand->childrenCount(); i += 1) {
        if (
            !isEqualUndoCommands(
                firstCommand->childAt(i),
                secondCommand->childAt(i)
            )
        ) {
            return false;
        }
    }

    return true;
}

void
jveHistory::slotSetUndoStackCurrentIndex(const int index)
{
    jveProjectMutex.lock();

    if (-2 < index && mp_undoStack.size() > index) {

        int i;

        // redo
        if (index > mp_undoStackCurrentIndex) {
            for (i = mp_undoStackCurrentIndex; i < (index + 1); i += 1) {
                mp_undoStack.at(i)->redo();
                mp_undoStack.at(i)->redoChildren();
            }
        // undo
        } else {
            for (i = mp_undoStackCurrentIndex; i > index; i -= 1) {
                mp_undoStack.at(i)->undoChildren();
                mp_undoStack.at(i)->undo();
            }
        }

        mp_undoStackCurrentIndex = index;

        mp_project->setModified(
            mp_undoStackCleanIndex != mp_undoStackCurrentIndex
        );
        emit jveHistorySignals.undoStackChanged(
            mp_undoStack.size(),
            mp_undoStackCurrentIndex,
            mp_undoStackCleanIndex,
            Q_NULLPTR
        );

    }

    jveProjectMutex.unlock();
}


