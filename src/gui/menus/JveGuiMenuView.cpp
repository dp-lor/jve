

#include "JveGuiMenuView.h"


#include "../definitions/JveGuiRulerType.h"
#include "../../core/signals/JveGlobalSignals.h"


JveGuiMenuView::JveGuiMenuView(QWidget *parent)
    : QMenu(parent),
        actionToggleTransportBar(this),
        mp_tbPositionGroup(this),
        actionTbTop(this),
        actionTbBottom(this),
        actionToggleRuler(this),
        mp_rulerTypeGroup(this),
        actionRulerTypeTF(this),
        actionRulerTypeT(this),
        actionRulerTypeF(this),
        actionToggleStatusBar(this),
        actionToggleFullScreen(this)
{
    // transport bar toggler
    actionToggleTransportBar.setCheckable(true);
    actionToggleTransportBar.setChecked(true);
    actionToggleTransportBar.setDisabled(true);

    // transport bar position group
    mp_tbPositionGroup.setExclusive(true);
    // transport bar top
    actionTbTop.setCheckable(true);
    actionTbTop.setData(false);
    mp_tbPositionGroup.addAction(&actionTbTop);
    // transport bar bottom
    actionTbBottom.setCheckable(true);
    actionTbBottom.setData(true);
    mp_tbPositionGroup.addAction(&actionTbBottom);
    // slot resend want set transport bar position
    connect(
        &mp_tbPositionGroup,
        SIGNAL(triggered(QAction *)),
        this,
        SLOT(slotResendWantSetTransportBarPosition(QAction *)),
        Qt::DirectConnection
    );

    // ruler toggler
    actionToggleRuler.setCheckable(true);
    connect(
        &actionToggleRuler,
        SIGNAL(toggled(bool)),
        this,
        SLOT(slotResendWantToggleRuler(bool)),
        Qt::DirectConnection
    );

    // ruler type group
    mp_rulerTypeGroup.setExclusive(true);
    // ruler type time and frames
    actionRulerTypeTF.setCheckable(true);
    actionRulerTypeTF.setData(JveGuiRulerType::TimeAndFrames);
    mp_rulerTypeGroup.addAction(&actionRulerTypeTF);
    // ruler type time
    actionRulerTypeT.setCheckable(true);
    actionRulerTypeT.setData(JveGuiRulerType::Time);
    mp_rulerTypeGroup.addAction(&actionRulerTypeT);
    // ruler type frames
    actionRulerTypeF.setCheckable(true);
    actionRulerTypeF.setData(JveGuiRulerType::Frames);
    mp_rulerTypeGroup.addAction(&actionRulerTypeF);
    // slot resend want set ruler type
    connect(
        &mp_rulerTypeGroup,
        SIGNAL(triggered(QAction *)),
        this,
        SLOT(slotResendWantSetRulerType(QAction *)),
        Qt::DirectConnection
    );

    // status bar toggler
    actionToggleStatusBar.setCheckable(true);
    connect(
        &actionToggleStatusBar,
        SIGNAL(toggled(bool)),
        &JveGlobalSignals,
        SIGNAL(wantToggleStatusBar(bool)),
        Qt::DirectConnection
    );

    // fullscreen toggler
    actionToggleFullScreen.setCheckable(true);
    actionToggleFullScreen.setShortcut(QKeySequence::FullScreen);
    connect(
        &actionToggleFullScreen,
        SIGNAL(toggled(bool)),
        &JveGlobalSignals,
        SIGNAL(wantToggleFullScreen(bool)),
        Qt::DirectConnection
    );

    // initial translate
    updateTranslations();

    // slot set up transport bar features
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSetUpTransportBarFeatures(bool)),
        this,
        SLOT(slotSetUpTransportBarFeatures(bool)),
        Qt::DirectConnection
    );
    // slot set up ruler features
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSetUpRulerFeatures(bool, int)),
        this,
        SLOT(slotSetUpRulerFeatures(bool, int)),
        Qt::DirectConnection
    );
    // slot set up status bar toggler
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSetUpStatusBarToggler(bool)),
        &actionToggleStatusBar,
        SLOT(setChecked(bool)),
        Qt::DirectConnection
    );
    // slot set up full screen toggler
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSetUpFullScreenToggler(bool)),
        &actionToggleFullScreen,
        SLOT(setChecked(bool)),
        Qt::DirectConnection
    );
}

JveGuiMenuView::~JveGuiMenuView(void)
{
}

void
JveGuiMenuView::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    } else {
        QMenu::changeEvent(event);
    }
}

void
JveGuiMenuView::addTransportBarFeatures(void)
{
    addAction(&actionToggleTransportBar);
    addAction(&actionTbTop);
    addAction(&actionTbBottom);
}

void
JveGuiMenuView::addRulerFeatures(void)
{
    addAction(&actionToggleRuler);
    addAction(&actionRulerTypeTF);
    addAction(&actionRulerTypeT);
    addAction(&actionRulerTypeF);
}

void
JveGuiMenuView::addToggleStatusBarAction(void)
{
    addAction(&actionToggleStatusBar);
}

void
JveGuiMenuView::addToggleFullScreenAction(void)
{
    addAction(&actionToggleFullScreen);
}

void
JveGuiMenuView::updateTranslations(void)
{
    // menu action
    menuAction()->setText(tr("gui_menu_view_text"));

    // transport bar toggler
    actionToggleTransportBar.setText(
        tr("gui_menu_view_action_toggle_transport_bar_text")
    );

    // transport bar top
    actionTbTop.setText(tr("gui_menu_view_action_transport_bar_top_text"));
    actionTbTop.setStatusTip(
        tr("gui_menu_view_action_transport_bar_top_status_tip")
    );

    // transport bar bottom
    actionTbBottom.setText(
        tr("gui_menu_view_action_transport_bar_bottom_text")
    );
    actionTbBottom.setStatusTip(
        tr("gui_menu_view_action_transport_bar_bottom_status_tip")
    );

    // ruler toggler
    actionToggleRuler.setText(tr("gui_menu_view_action_toggle_ruler_text"));
    actionToggleRuler.setStatusTip(
        tr("gui_menu_view_action_toggle_ruler_status_tip")
    );

    // ruler type time and frames
    actionRulerTypeTF.setText(
        tr("gui_menu_view_action_ruler_type_time_and_frames_text")
    );
    actionRulerTypeTF.setStatusTip(
        tr("gui_menu_view_action_ruler_type_time_and_frames_status_tip")
    );

    // ruler type time
    actionRulerTypeT.setText(
        tr("gui_menu_view_action_ruler_type_time_text")
    );
    actionRulerTypeT.setStatusTip(
        tr("gui_menu_view_action_ruler_type_time_status_tip")
    );

    // ruler type frames
    actionRulerTypeF.setText(
        tr("gui_menu_view_action_ruler_type_frames_text")
    );
    actionRulerTypeF.setStatusTip(
        tr("gui_menu_view_action_ruler_type_frames_status_tip")
    );

    // status bar
    actionToggleStatusBar.setText(
        tr("gui_menu_view_action_toggle_status_bar_text")
    );
    actionToggleStatusBar.setStatusTip(
        tr("gui_menu_view_action_toggle_status_bar_status_tip")
    );

    // full screen
    actionToggleFullScreen.setText(
        tr("gui_menu_view_action_toggle_full_screen_text")
    );
    actionToggleFullScreen.setStatusTip(
        tr("gui_menu_view_action_toggle_full_screen_status_tip")
    );
}

void
JveGuiMenuView::slotSetUpTransportBarFeatures(const bool position)
{
    actionTbTop    .setChecked(!position);
    actionTbBottom .setChecked( position);
}

void
JveGuiMenuView::slotSetUpRulerFeatures(const bool checked, const int type)
{
    actionToggleRuler.setChecked(checked);
    mp_rulerTypeGroup.setEnabled(checked);

    actionRulerTypeTF .setChecked(JveGuiRulerType::TimeAndFrames == type);
    actionRulerTypeT  .setChecked(JveGuiRulerType::Time          == type);
    actionRulerTypeF  .setChecked(JveGuiRulerType::Frames        == type);
}

void
JveGuiMenuView::slotResendWantSetTransportBarPosition(QAction *action)
{
    if (nullptr != action) {
        JveGlobalSignals.wantSetTransportBarPosition(action->data().toBool());
    }
}

void
JveGuiMenuView::slotResendWantToggleRuler(const bool status)
{
    mp_rulerTypeGroup.setEnabled(status);
    JveGlobalSignals.wantToggleRuler(status);
}

void
JveGuiMenuView::slotResendWantSetRulerType(QAction *action)
{
    if (nullptr != action) {
        JveGlobalSignals.wantSetRulerType(action->data().toInt());
    }
}


