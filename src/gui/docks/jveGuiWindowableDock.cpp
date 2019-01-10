

#include "jveGuiWindowableDock.h"


#include <QAction>


#include "../windows/jveGuiDockableWindow.h"


jveGuiWindowableDock::jveGuiWindowableDock(
    QMainWindow          *parent,
    jveGuiDockableWindow *window
) : jveGuiDock(parent),
        mp_protectedWrapper(this),
        mp_protectedWrapperLayout(&mp_protectedWrapper),
        mp_protectedView(Q_NULLPTR),
        mp_window(window),
        mp_toggleWindowAction(mp_window->toggleAction())
{
    // fix window visibility state
    mp_window->fixVisibilityState(mp_toggleViewAction->isChecked());

    // wrapper
    mp_protectedWrapper.setFocusPolicy(Qt::NoFocus);
    mp_protectedWrapper.setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    setWidget(&mp_protectedWrapper);

    // wrapper layout
    mp_protectedWrapperLayout.setMargin(0);
    mp_protectedWrapperLayout.setSpacing(0);

    // toggle view
    connect(
        mp_toggleViewAction,
        SIGNAL(triggered(bool)),
        this,
        SLOT(slotViewTogglerTriggered(bool)),
        Qt::DirectConnection
    );
    // toggle window
    connect(
        mp_toggleWindowAction,
        SIGNAL(triggered(bool)),
        this,
        SLOT(slotWindowTogglerTriggered(bool)),
        Qt::DirectConnection
    );
    // close window
    connect(
        mp_window,
        SIGNAL(closedWithoutToggler()),
        this,
        SLOT(slotWindowClosedWithoutToggler()),
        Qt::DirectConnection
    );
}

jveGuiWindowableDock::~jveGuiWindowableDock(void)
{
}

void
jveGuiWindowableDock::setView(QWidget *view)
{
    mp_protectedView = view;

    if (Q_NULLPTR != mp_protectedView) {
        if (mp_window->isVisibleFromSettings()) {
            mp_window->attachView(mp_protectedView);
        } else {
            mp_protectedWrapperLayout.addWidget(mp_protectedView);
        }
    }
}

void
jveGuiWindowableDock::initialShow(void)
{
    if (mp_window->isVisibleFromSettings()) {
        mp_window->show();
    }
}

void
jveGuiWindowableDock::finalClose(void)
{
    mp_window->saveSettings();
    mp_window->setForcedClosing(true);
    mp_window->close();
}

QAction *
jveGuiWindowableDock::toggleWindowAction(void)
{
    return mp_toggleWindowAction;
}

void
jveGuiWindowableDock::attachViewToSelf(void)
{
    if (Q_NULLPTR != mp_protectedView) {
        mp_window->detachView(mp_protectedView);
        mp_protectedWrapperLayout.addWidget(mp_protectedView);
    }
}

void
jveGuiWindowableDock::attachViewToWindow(void)
{
    if (Q_NULLPTR != mp_protectedView) {
        mp_protectedWrapperLayout.removeWidget(mp_protectedView);
        mp_window->attachView(mp_protectedView);
    }
}

void
jveGuiWindowableDock::slotViewTogglerTriggered(const bool toVisible)
{
    if (toVisible && mp_toggleWindowAction->isChecked()) {
        mp_toggleWindowAction->setChecked(false);
        mp_window->setVisible(false);
        attachViewToSelf();
    }
}

void
jveGuiWindowableDock::slotWindowTogglerTriggered(const bool toVisible)
{
    if (toVisible) {
        if (mp_toggleViewAction->isChecked()) {
            mp_toggleViewAction->trigger();
        }
        attachViewToWindow();
        mp_window->setVisible(true);
    } else {
        mp_window->setVisible(false);
        attachViewToSelf();
    }
}

void
jveGuiWindowableDock::slotWindowClosedWithoutToggler(void)
{
    attachViewToSelf();
}


