

#include "JveGuiMenuFile.h"


#include "../../core/definitions/JveState.h"

#include "../../core/signals/JveGlobalSignals.h"
#include "../../core/signals/JveProjectSignals.h"


JveGuiMenuFile::JveGuiMenuFile(QWidget *parent)
    : QMenu(parent),
        actionNew(this),
        actionOpen(this),
        menuRecent(this),
        actionSave(this),
        actionSaveAs(this),
        actionRender(this),
        actionClose(this),
        actionExit(this)
{
    // new
    actionNew.setShortcut(QKeySequence::New);
    actionNew.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionNew);
    connect(
        &actionNew,
        SIGNAL(triggered()),
        &JveProjectSignals,
        SIGNAL(wantLoadNewProject()),
        Qt::DirectConnection
    );

    // open
    actionOpen.setShortcut(QKeySequence::Open);
    actionOpen.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionOpen);
    connect(
        &actionOpen,
        SIGNAL(triggered()),
        &JveProjectSignals,
        SIGNAL(wantShowOpenProjectDialog()),
        Qt::DirectConnection
    );

    // recent submenu
    addAction(menuRecent.menuAction());

    // separator
    addSeparator();

    // save
    actionSave.setShortcut(QKeySequence::Save);
    actionSave.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionSave);
    connect(
        &actionSave,
        SIGNAL(triggered()),
        &JveProjectSignals,
        SIGNAL(wantSaveProject()),
        Qt::DirectConnection
    );

    // save as
    actionSaveAs.setShortcut(QKeySequence::SaveAs);
    actionSaveAs.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionSaveAs);
    connect(
        &actionSaveAs,
        SIGNAL(triggered()),
        &JveProjectSignals,
        SIGNAL(wantShowSaveProjectDialog()),
        Qt::DirectConnection
    );

    // separator
    addSeparator();

    // render
    actionRender.setShortcut(QKeySequence::Refresh);
    actionRender.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionRender);
    connect(
        &actionRender,
        SIGNAL(triggered()),
        &JveProjectSignals,
        SIGNAL(wantShowRenderProjectDialog()),
        Qt::DirectConnection
    );

    // separator
    addSeparator();

    // close
    actionClose.setShortcut(QKeySequence::Close);
    actionClose.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionClose);
    connect(
        &actionClose,
        SIGNAL(triggered()),
        &JveProjectSignals,
        SIGNAL(wantCloseProject()),
        Qt::DirectConnection
    );

    // exit
    actionExit.setShortcut(QKeySequence::Quit);
    actionExit.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionExit);
    connect(
        &actionExit,
        SIGNAL(triggered()),
        &JveGlobalSignals,
        SIGNAL(wantExit()),
        Qt::DirectConnection
    );

    // initial state
    slotStateChanged(JveState::None);

    // initial translate
    updateTranslations();

    // slot state changed
    connect(
        &JveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotStateChanged(int)),
        Qt::QueuedConnection
    );
}

JveGuiMenuFile::~JveGuiMenuFile()
{
}

void
JveGuiMenuFile::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    } else {
        QMenu::changeEvent(event);
    }
}

void
JveGuiMenuFile::updateTranslations(void)
{
    // menu action
    menuAction()->setText(tr("gui_menu_file_text"));

    // new
    actionNew.setText(tr("gui_menu_file_action_new_text"));
    actionNew.setStatusTip(tr("gui_menu_file_action_new_status_tip"));

    // open
    actionOpen.setText(tr("gui_menu_file_action_open_text"));
    actionOpen.setStatusTip(tr("gui_menu_file_action_open_status_tip"));

    // save
    actionSave.setText(tr("gui_menu_file_action_save_text"));
    actionSave.setStatusTip(tr("gui_menu_file_action_save_status_tip"));

    // save as
    actionSaveAs.setText(tr("gui_menu_file_action_save_as_text"));
    actionSaveAs.setStatusTip(tr("gui_menu_file_action_save_as_status_tip"));

    // render
    actionRender.setText(tr("gui_menu_file_action_render_text"));
    actionRender.setStatusTip(tr("gui_menu_file_action_render_status_tip"));

    // close
    actionClose.setText(tr("gui_menu_file_action_close_text"));
    actionClose.setStatusTip(tr("gui_menu_file_action_close_status_tip"));

    // exit
    actionExit.setText(tr("gui_menu_file_action_exit_text"));
    actionExit.setStatusTip(tr("gui_menu_file_action_exit_status_tip"));
}

void
JveGuiMenuFile::slotStateChanged(const int state)
{
    bool isBusy         = state & JveState::Busy;
    bool isBusyOrClosed = isBusy || !(state & JveState::ProjectOpened);

    // busy
    actionNew  .setDisabled(isBusy);
    actionOpen .setDisabled(isBusy);

    // busy/closed
    actionSave   .setDisabled(isBusyOrClosed);
    actionSaveAs .setDisabled(isBusyOrClosed);
    actionRender .setDisabled(isBusyOrClosed);
    actionClose  .setDisabled(isBusyOrClosed);
}


