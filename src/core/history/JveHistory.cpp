

#include "JveHistory.h"


#include "../signals/JveHistorySignals.h"

#include "../mutexes/JveProjectMutex.h"
#include "../application/JveProject.h"

#include "JveUndoCommand.h"

#include "JveProjectLoadedCommand.h"
#include "JveNewProjectLoadedCommand.h"
#include "JveSetRangeStartCommand.h"
#include "JveSetRangeEndCommand.h"

#include "JveProjectLoadedCommandInfo.h"
#include "JveNewProjectLoadedCommandInfo.h"
#include "JveSetRangeStartCommandInfo.h"
#include "JveSetRangeEndCommandInfo.h"


JveHistory::JveHistory(JveProject *project)
    : QObject(nullptr),
        mp_project(project),
        mp_undoStackCurrentIndex(-1),
        mp_undoStackCleanIndex(-1),
        mp_undoStack()
{
    // slot set undo stack current index
    connect(
        &JveHistorySignals,
        SIGNAL(wantSetUndoStackCurrentIndex(int)),
        this,
        SLOT(slotSetUndoStackCurrentIndex(int)),
        Qt::QueuedConnection
    );
}

JveHistory::~JveHistory(void)
{
    mp_undoStack.clear();
}

void
JveHistory::clear(void)
{
    mp_undoStackCurrentIndex = -1;
    mp_undoStackCleanIndex   = -1;

    mp_undoStack.clear();
    emit JveHistorySignals.undoStackChanged(
        mp_undoStack.size(),
        mp_undoStackCurrentIndex,
        mp_undoStackCleanIndex,
        nullptr
    );
}

void
JveHistory::setProjectLoadedState(void)
{
    mp_undoStackCleanIndex = 0;
    appendUndoCommandWithModifiedState(
        new JveProjectLoadedCommand(), false);
}

void
JveHistory::setNewProjectLoadedState(void)
{
    mp_undoStackCleanIndex = 0;
    appendUndoCommandWithModifiedState(
        new JveNewProjectLoadedCommand(), false);
}

void
JveHistory::appendUndoCommand(JveUndoCommand *undoCommand)
{
    appendUndoCommandWithModifiedState(undoCommand, true);
}

void
JveHistory::setUndoStackClean(void)
{
    if (mp_undoStackCleanIndex != mp_undoStackCurrentIndex) {
        mp_undoStackCleanIndex = mp_undoStackCurrentIndex;
        mp_project->setModified(false);
        emit JveHistorySignals.undoStackChanged(
            mp_undoStack.size(),
            mp_undoStackCurrentIndex,
            mp_undoStackCleanIndex,
            nullptr
        );
    }
}

void
JveHistory::appendUndoCommandWithModifiedState(
          JveUndoCommand *undoCommand,
    const bool            modified
)
{
    JveUndoCommandInfo *undoCommandInfo     = nullptr;
    int                 nextCommandIndex    = mp_undoStackCurrentIndex + 1;
    bool                canAppendNewCommand = true;

    // not last index
    if (mp_undoStackCurrentIndex < (mp_undoStack.size() - 1)) {

        JveUndoCommand *nextUndoCommand = mp_undoStack.at(nextCommandIndex);

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
    emit JveHistorySignals.undoStackChanged(
        mp_undoStack.size(),
        mp_undoStackCurrentIndex,
        mp_undoStackCleanIndex,
        undoCommandInfo
    );
}

bool
JveHistory::isEqualUndoCommands(
    JveUndoCommand *firstCommand,
    JveUndoCommand *secondCommand
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
    for (int i = 0; i < firstCommand->childrenCount(); i++) {
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
JveHistory::slotSetUndoStackCurrentIndex(const int index)
{
    JveProjectMutex.lock();

    if (-2 < index && mp_undoStack.size() > index) {

        int i;

        // redo
        if (index > mp_undoStackCurrentIndex) {
            for (i = mp_undoStackCurrentIndex; i < (index + 1); i++) {
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
        emit JveHistorySignals.undoStackChanged(
            mp_undoStack.size(),
            mp_undoStackCurrentIndex,
            mp_undoStackCleanIndex,
            nullptr
        );

    }

    JveProjectMutex.unlock();
}


