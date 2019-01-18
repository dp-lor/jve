

#include "JveGuiMenuRecent.h"


#include "../../core/definitions/JveState.h"

#include "../../core/application/JveSettings.h"

#include "../../core/signals/JveGlobalSignals.h"
#include "../../core/signals/JveProjectSignals.h"


#include "../definitions/JveGuiAppearanceDefines.h"
#include "../definitions/JveGuiSettingsDefines.h"


JveGuiMenuRecent::JveGuiMenuRecent(QWidget *parent)
    : QMenu(parent),
        mp_actionClear(this)
{
    // init
    mp_fileInfo.setCaching(false);

    // create recent actions
    for (int i = 0; i < JVE_GUI_MENU_RECENT_MAX_NUMBER; i++) {
        JveGuiAction *actionRecent = new JveGuiAction(this);
        mp_recentActions.append(actionRecent);
        addAction(actionRecent);
        connect(
            actionRecent,
            SIGNAL(triggered()),
            this,
            SLOT(slotCatchWantLoadProject()),
            Qt::DirectConnection
        );
    }

    // separator
    addSeparator();

    // clear action
    addAction(&mp_actionClear);
    connect(
        &mp_actionClear,
        SIGNAL(triggered()),
        this,
        SLOT(slotClearRecentItems()),
        Qt::DirectConnection
    );

    // restore recent items
    JveSettings.lock();

    if (
        JveSettings.contains(
            JVE_GUI_SETTINGS_RECENT_PROJECTS
        )
    ) {
        mp_recentItems = JveSettings.value(
            JVE_GUI_SETTINGS_RECENT_PROJECTS
        ).toStringList();
    }

    JveSettings.unlock();

    // initial state
    truncateRecentItems();
    slotUpdateRecentItems();
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

    // slot add recent item
    connect(
        &JveProjectSignals,
        SIGNAL(wantAddToRecentItems(QString)),
        this,
        SLOT(slotAddRecentItem(QString)),
        Qt::QueuedConnection
    );

    // slot hovered update
    connect(
        menuAction(),
        SIGNAL(hovered()),
        this,
        SLOT(slotUpdateRecentItems()),
        Qt::DirectConnection
    );
}

JveGuiMenuRecent::~JveGuiMenuRecent()
{
    JveSettings.lock();

    JveSettings.setValue(
        JVE_GUI_SETTINGS_RECENT_PROJECTS,
        mp_recentItems
    );

    JveSettings.sync();
    JveSettings.unlock();
}

void
JveGuiMenuRecent::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
JveGuiMenuRecent::truncateRecentItems(const bool toEmpty)
{
    int truncateTo = toEmpty
        ? 0
        : JVE_GUI_MENU_RECENT_MAX_NUMBER;

    while (mp_recentItems.size() > truncateTo) {
        mp_recentItems.removeLast();
    }
}

void
JveGuiMenuRecent::updateMenuActionState(void)
{
    menuAction()->setDisabled(
        mp_state & JveState::Busy
            || mp_recentItems.isEmpty()
    );
}

void
JveGuiMenuRecent::updateTranslations(void)
{
    // menu action
    menuAction()->setText(tr("gui_menu_recent_text"));
    menuAction()->setStatusTip(tr("gui_menu_recent_status_tip"));

    // clear recent
    mp_actionClear.setText(tr("gui_menu_recent_action_clear_text"));
    mp_actionClear.setStatusTip(
        tr("gui_menu_recent_action_clear_status_tip")
    );
}

void
JveGuiMenuRecent::slotStateChanged(const int state)
{
    mp_state = state;
    updateMenuActionState();
}

void
JveGuiMenuRecent::slotUpdateRecentItems(void)
{
    updateMenuActionState();

    for (int i = 0; i < JVE_GUI_MENU_RECENT_MAX_NUMBER; i++) {
        JveGuiAction *actionRecent = mp_recentActions.at(i);
        if (i < mp_recentItems.size()) {
            QString projectFilePath = mp_recentItems.at(i);
            mp_fileInfo.setFile(projectFilePath);
            actionRecent->setData(projectFilePath);
            actionRecent->setVisible(true);
            actionRecent->setDisabled(
                !mp_fileInfo.exists()
                    || !mp_fileInfo.isReadable()
                    ||  mp_fileInfo.isDir()
            );
            actionRecent->setText(
                QString("&%1  %2")
                    .arg(i + 1)
                    .arg(mp_fileInfo.fileName())
            );
            actionRecent->setStatusTip(projectFilePath);
        } else {
            actionRecent->setVisible(false);
        }
    }
}

void
JveGuiMenuRecent::slotAddRecentItem(const QString &projectFilePath)
{
    mp_recentItems.removeAll(projectFilePath);
    mp_recentItems.prepend(projectFilePath);
    truncateRecentItems();
    slotUpdateRecentItems();
}

void
JveGuiMenuRecent::slotCatchWantLoadProject(void)
{
    JveGuiAction *action = static_cast<JveGuiAction *>(sender());

    if (nullptr != action) {
        emit JveProjectSignals.wantLoadProject(action->data().toString());
    }
}

void
JveGuiMenuRecent::slotClearRecentItems(void)
{
    truncateRecentItems(true);
    slotUpdateRecentItems();
}


