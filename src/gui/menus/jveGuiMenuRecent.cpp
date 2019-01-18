

#include "jveGuiMenuRecent.h"


#include "../../core/definitions/jveState.h"

#include "../../core/application/jveSettings.h"

#include "../../core/signals/jveGlobalSignals.h"
#include "../../core/signals/jveProjectSignals.h"


#include "../definitions/jveGuiAppearanceDefines.h"
#include "../definitions/jveGuiSettingsDefines.h"


jveGuiMenuRecent::jveGuiMenuRecent(QWidget *parent)
    : QMenu(parent),
        mp_actionClear(this)
{
    // init
    mp_fileInfo.setCaching(false);

    // create recent actions
    for (int i = 0; i < JVE_GUI_MENU_RECENT_MAX_NUMBER; i += 1) {
        jveGuiAction *actionRecent = new jveGuiAction(this);
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
    jveSettings.lock();

    if (
        jveSettings.contains(
            JVE_GUI_SETTINGS_RECENT_PROJECTS
        )
    ) {
        mp_recentItems = jveSettings.value(
            JVE_GUI_SETTINGS_RECENT_PROJECTS
        ).toStringList();
    }

    jveSettings.unlock();

    // initial state
    truncateRecentItems();
    slotUpdateRecentItems();
    slotStateChanged(jveState::None);

    // initial translate
    updateTranslations();

    // slot state changed
    connect(
        &jveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotStateChanged(int)),
        Qt::QueuedConnection
    );

    // slot add recent item
    connect(
        &jveProjectSignals,
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

jveGuiMenuRecent::~jveGuiMenuRecent()
{
    jveSettings.lock();

    jveSettings.setValue(
        JVE_GUI_SETTINGS_RECENT_PROJECTS,
        mp_recentItems
    );

    jveSettings.sync();
    jveSettings.unlock();
}

void
jveGuiMenuRecent::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
jveGuiMenuRecent::truncateRecentItems(const bool toEmpty)
{
    int truncateTo = toEmpty
        ? 0
        : JVE_GUI_MENU_RECENT_MAX_NUMBER;

    while (mp_recentItems.size() > truncateTo) {
        mp_recentItems.removeLast();
    }
}

void
jveGuiMenuRecent::updateMenuActionState(void)
{
    menuAction()->setDisabled(
        mp_state & jveState::Busy
            || mp_recentItems.isEmpty()
    );
}

void
jveGuiMenuRecent::updateTranslations(void)
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
jveGuiMenuRecent::slotStateChanged(const int state)
{
    mp_state = state;
    updateMenuActionState();
}

void
jveGuiMenuRecent::slotUpdateRecentItems(void)
{
    updateMenuActionState();

    for (int i = 0; i < JVE_GUI_MENU_RECENT_MAX_NUMBER; i += 1) {
        jveGuiAction *actionRecent = mp_recentActions.at(i);
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
jveGuiMenuRecent::slotAddRecentItem(const QString &projectFilePath)
{
    mp_recentItems.removeAll(projectFilePath);
    mp_recentItems.prepend(projectFilePath);
    truncateRecentItems();
    slotUpdateRecentItems();
}

void
jveGuiMenuRecent::slotCatchWantLoadProject(void)
{
    jveGuiAction *action = static_cast<jveGuiAction *>(sender());

    if (Q_NULLPTR != action) {
        emit jveProjectSignals.wantLoadProject(action->data().toString());
    }
}

void
jveGuiMenuRecent::slotClearRecentItems(void)
{
    truncateRecentItems(true);
    slotUpdateRecentItems();
}


