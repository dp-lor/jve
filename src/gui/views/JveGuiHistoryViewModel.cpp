

#include "JveGuiHistoryViewModel.h"


#include <QtMath>
#include <QApplication>
#include <QPalette>


#include "../definitions/JveGuiMediaDefines.h"

#include "../../core/definitions/JveUndoCommandType.h"
#include "../../core/history/JveUndoCommandInfo.h"
#include "../../core/signals/JveHistorySignals.h"


JveGuiHistoryViewModel::JveGuiHistoryViewModel(QObject *parent)
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
        &JveHistorySignals,
        SIGNAL(undoStackChanged(int, int, int, JveUndoCommandInfo *)),
        this,
        SLOT(slotChangeUndoStack(int, int, int, JveUndoCommandInfo *)),
        Qt::QueuedConnection
    );

    // slot undo
    connect(
        &JveHistorySignals,
        SIGNAL(wantUndo()),
        this,
        SLOT(slotUndo()),
        Qt::DirectConnection
    );
    // slot redo
    connect(
        &JveHistorySignals,
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

JveGuiHistoryViewModel::~JveGuiHistoryViewModel(void)
{
    mp_infoStack.clear();
}

int
JveGuiHistoryViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return mp_infoStack.size();
}

QVariant
JveGuiHistoryViewModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
        case Qt::DisplayRole:
            return mp_infoStack.at(index.row())->text();
        case Qt::DecorationRole:
            return mp_cleanIndex == index.row()
                ? mp_cleanIconPixmap
                : mp_dummyIcon;
        /*case Qt::ToolTipRole:
            TODO maybe short text and more explained tooltip?*/
    }

    return QVariant();
}

void
JveGuiHistoryViewModel::updateIcons(void)
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
JveGuiHistoryViewModel::updateTranslations(void)
{
    mp_infoStackMutex.lock();

    for (int i = 0; i < mp_infoStack.size(); i++) {
        updateCommandInfoText(mp_infoStack.at(i));
    }

    mp_infoStackMutex.unlock();
}

void
JveGuiHistoryViewModel::clear(void)
{
    slotChangeUndoStack(0, -1, -1, nullptr);
}

void
JveGuiHistoryViewModel::updateCommandInfoText(JveUndoCommandInfo *commandInfo)
{
    switch (commandInfo->type()) {

        // project loaded
        case JveUndoCommandType::ProjectLoaded:
            commandInfo->setText(
                tr("undo_command_project_loaded_text")
            );
        break;

        // new project loaded
        case JveUndoCommandType::NewProjectLoaded:
            commandInfo->setText(
                tr("undo_command_new_project_loaded_text")
            );
        break;

        // range start
        case JveUndoCommandType::SetRangeStart:
            commandInfo->setText(
                tr("undo_command_set_range_start_text%1")
            );
        break;

        // range end
        case JveUndoCommandType::SetRangeEnd:
            commandInfo->setText(
                tr("undo_command_set_range_end_text%1")
            );
        break;
    }
}

void
JveGuiHistoryViewModel::slotChangeUndoStack(
    const int                 stackSize,
    const int                 currentIndex,
    const int                 cleanIndex,
          JveUndoCommandInfo *undoCommandInfo
)
{
    mp_infoStackMutex.lock();
    mp_userCanChangeStack = false;

    bool hasNewUndoCommandInfo = nullptr != undoCommandInfo;
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

    emit JveHistorySignals.historyActionsStateChanged(
        // can undo
        mp_currentIndex > 0,
        // can redo
        mp_currentIndex < (newTmpInfoStackSize - 1)
    );

    mp_userCanChangeStack = true;
    mp_infoStackMutex.unlock();
}

void
JveGuiHistoryViewModel::slotUndo(void)
{
    mp_infoStackMutex.lock();

    if (mp_currentIndex > 0) {
        emit JveHistorySignals
                .wantSetUndoStackCurrentIndex(mp_currentIndex - 1);
    }

    mp_infoStackMutex.unlock();
}

void
JveGuiHistoryViewModel::slotRedo(void)
{
    mp_infoStackMutex.lock();

    if (mp_currentIndex < mp_infoStack.size() - 1) {
        emit JveHistorySignals
                .wantSetUndoStackCurrentIndex(mp_currentIndex + 1);
    }

    mp_infoStackMutex.unlock();
}

void
JveGuiHistoryViewModel::slotCatchCurrentChanged(
    const QModelIndex &currentIndex
)
{
    if (
        mp_userCanChangeStack
            && mp_currentIndex != currentIndex.row()
    ) {
        emit JveHistorySignals
                .wantSetUndoStackCurrentIndex(currentIndex.row());
    }
}


