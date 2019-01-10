

#include "jveGuiHistoryViewModel.h"


#include <QtMath>
#include <QApplication>
#include <QPalette>


#include "../definitions/jveGuiMediaDefines.h"

#include "../../core/definitions/jveUndoCommandType.h"
#include "../../core/history/jveUndoCommandInfo.h"
#include "../../core/signals/jveHistorySignals.h"


jveGuiHistoryViewModel::jveGuiHistoryViewModel(QObject *parent)
    : QAbstractListModel(parent),
        selectionModel(this, this),
        mp_infoStackMutex(QMutex::NonRecursive),
        mp_infoStack(),
        mp_userCanChangeStack(true),
        mp_currentIndex(-1),
        mp_cleanIndex(-1),
        mp_dummyIcon(JVE_GUI_ICON_DUMMY),
        mp_cleanIconPixmap(JVE_GUI_ICON_HISTORY_CLEAN),
        mp_cleanIconMask(
            mp_cleanIconPixmap
                .createMaskFromColor(Qt::black, Qt::MaskOutColor)
        )
{
    // initial state
    clear();
    updateIcons();

    // slot change undo stack
    connect(
        &jveHistorySignals,
        SIGNAL(undoStackChanged(int, int, int, jveUndoCommandInfo *)),
        this,
        SLOT(slotChangeUndoStack(int, int, int, jveUndoCommandInfo *)),
        Qt::QueuedConnection
    );

    // slot undo
    connect(
        &jveHistorySignals,
        SIGNAL(wantUndo()),
        this,
        SLOT(slotUndo()),
        Qt::DirectConnection
    );
    // slot redo
    connect(
        &jveHistorySignals,
        SIGNAL(wantRedo()),
        this,
        SLOT(slotRedo()),
        Qt::DirectConnection
    );
    // slot catch current changed
    connect(
        &selectionModel,
        SIGNAL(currentChanged(QModelIndex, QModelIndex)),
        this,
        SLOT(slotCatchCurrentChanged(QModelIndex)),
        Qt::DirectConnection
    );
}

jveGuiHistoryViewModel::~jveGuiHistoryViewModel(void)
{
    mp_infoStack.clear();
}

int
jveGuiHistoryViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return mp_infoStack.size();
}

QVariant
jveGuiHistoryViewModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
        case Qt::DisplayRole:
            return mp_infoStack.at(index.row())->text();
        break;
        case Qt::DecorationRole:
            return mp_cleanIndex == index.row()
                ? mp_cleanIconPixmap
                : mp_dummyIcon;
        break;
        /*case Qt::ToolTipRole:
            TODO maybe short text and more explained tooltip?
        break;*/
    }

    return QVariant();
}

void
jveGuiHistoryViewModel::updateIcons(void)
{
    if (mp_currentIndex == mp_cleanIndex) {
        mp_cleanIconPixmap.fill(
            qApp->palette().color(QPalette::HighlightedText)
        );
    } else {
        mp_cleanIconPixmap.fill(
            qApp->palette().color(QPalette::Disabled, QPalette::ButtonText)
        );
    }

    mp_cleanIconPixmap.setMask(mp_cleanIconMask);
}

void
jveGuiHistoryViewModel::updateTranslations(void)
{
    mp_infoStackMutex.lock();

    for (int i = 0; i < mp_infoStack.size(); i += 1) {
        updateCommandInfoText(mp_infoStack.at(i));
    }

    mp_infoStackMutex.unlock();
}

void
jveGuiHistoryViewModel::clear(void)
{
    slotChangeUndoStack(0, -1, -1, Q_NULLPTR);
}

void
jveGuiHistoryViewModel::updateCommandInfoText(jveUndoCommandInfo *commandInfo)
{
    switch (commandInfo->type()) {

        // project loaded
        case jveUndoCommandType::ProjectLoaded:
            commandInfo->setText(
                tr("undo_command_project_loaded_text")
            );
        break;

        // new project loaded
        case jveUndoCommandType::NewProjectLoaded:
            commandInfo->setText(
                tr("undo_command_new_project_loaded_text")
            );
        break;

        // range start
        case jveUndoCommandType::SetRangeStart:
            commandInfo->setText(
                tr("undo_command_set_range_start_text%1")
            );
        break;

        // range end
        case jveUndoCommandType::SetRangeEnd:
            commandInfo->setText(
                tr("undo_command_set_range_end_text%1")
            );
        break;
    }
}

void
jveGuiHistoryViewModel::slotChangeUndoStack(
    const int                 stackSize,
    const int                 currentIndex,
    const int                 cleanIndex,
          jveUndoCommandInfo *undoCommandInfo
)
{
    mp_infoStackMutex.lock();
    mp_userCanChangeStack = false;

    bool hasNewUndoCommandInfo = Q_NULLPTR != undoCommandInfo;
    int  currentInfoStackSize  = mp_infoStack.size();
    int  newTmpInfoStackSize   = qMin(
        stackSize - (hasNewUndoCommandInfo ? 1 : 0),
        currentInfoStackSize
    );

    if (currentInfoStackSize > newTmpInfoStackSize) {
        emit beginRemoveRows(
            QModelIndex(),
            newTmpInfoStackSize,
            currentInfoStackSize - 1
        );
        while (newTmpInfoStackSize < mp_infoStack.size()) {
            mp_infoStack.removeLast();
        }
        emit endRemoveRows();
    }

    if (hasNewUndoCommandInfo) {
        updateCommandInfoText(undoCommandInfo);
        emit beginInsertRows(
            QModelIndex(),
            newTmpInfoStackSize,
            newTmpInfoStackSize
        );
        mp_infoStack.append(undoCommandInfo);
        emit endInsertRows();
    }

    mp_currentIndex = currentIndex;
    mp_cleanIndex   = cleanIndex;

    updateIcons();

    selectionModel.setCurrentIndex(
        createIndex(mp_currentIndex, 0),
        QItemSelectionModel::ClearAndSelect
    );

    emit jveHistorySignals.historyActionsStateChanged(
        // can undo
        mp_currentIndex > 0,
        // can redo
        mp_currentIndex < (newTmpInfoStackSize - 1)
    );

    mp_userCanChangeStack = true;
    mp_infoStackMutex.unlock();
}

void
jveGuiHistoryViewModel::slotUndo(void)
{
    mp_infoStackMutex.lock();

    if (mp_currentIndex > 0) {
        emit jveHistorySignals
                .wantSetUndoStackCurrentIndex(mp_currentIndex - 1);
    }

    mp_infoStackMutex.unlock();
}

void
jveGuiHistoryViewModel::slotRedo(void)
{
    mp_infoStackMutex.lock();

    if (mp_currentIndex < mp_infoStack.size() - 1) {
        emit jveHistorySignals
                .wantSetUndoStackCurrentIndex(mp_currentIndex + 1);
    }

    mp_infoStackMutex.unlock();
}

void
jveGuiHistoryViewModel::slotCatchCurrentChanged(
    const QModelIndex &currentIndex
)
{
    if (
        mp_userCanChangeStack
            && mp_currentIndex != currentIndex.row()
    ) {
        emit jveHistorySignals
                .wantSetUndoStackCurrentIndex(currentIndex.row());
    }
}


