

#include "JveGuiWindowableDock.h"


#include <QAction>


#include "../windows/JveGuiDockableWindow.h"


JveGuiWindowableDock::JveGuiWindowableDock(
    QMainWindow          *parent,
    JveGuiDockableWindow *window
) : JveGuiDock(parent),
        mp_protectedWrapper(this),
        mp_protectedWrapperLayout(&mp_protectedWrapper),
        mp_protectedView(nullptr),
        mp_window(window),
        mp_toggleWindowAction(mp_window->toggleAction())
{
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

    // slot toggle view
    connect(
        mp_toggleViewAction,
        SIGNAL(triggered(bool)),
        this,
        SLOT(slotViewTogglerTriggered(bool)),
        Qt::DirectConnection
    );
    // slot toggle window
    connect(
        mp_toggleWindowAction,
        SIGNAL(triggered(bool)),
        this,
        SLOT(slotWindowTogglerTriggered(bool)),
        Qt::DirectConnection
    );
    // slot window closed without toggler
    connect(
        mp_window,
        SIGNAL(closedWithoutToggler()),
        this,
        SLOT(slotWindowClosedWithoutToggler()),
        Qt::DirectConnection
    );
}

JveGuiWindowableDock::~JveGuiWindowableDock(void)
{
}

void
JveGuiWindowableDock::setView(QWidget *view)
{
    mp_protectedView = view;
}

void
JveGuiWindowableDock::setUp(void)
{
    // fix window visibility state
    mp_window->fixVisibleBySettings(mp_toggleViewAction->isChecked());

    if (nullptr != mp_protectedView) {
        if (mp_window->isVisibleBySettings()) {
            mp_window->attachView(mp_protectedView);
        } else {
            mp_protectedWrapperLayout.addWidget(mp_protectedView);
        }
    }

    if (mp_window->isVisibleBySettings()) {
        mp_window->show();
    }
}

void
JveGuiWindowableDock::upSet(void)
{
    mp_window->setForcedClosing(true);
    mp_window->close();
}

QAction *
JveGuiWindowableDock::toggleWindowAction(void)
{
    return mp_toggleWindowAction;
}

void
JveGuiWindowableDock::attachViewToSelf(void)
{
    if (nullptr != mp_protectedView) {
        mp_window->detachView(mp_protectedView);
        mp_protectedWrapperLayout.addWidget(mp_protectedView);
    }
}

void
JveGuiWindowableDock::attachViewToWindow(void)
{
    if (nullptr != mp_protectedView) {
        mp_protectedWrapperLayout.removeWidget(mp_protectedView);
        mp_window->attachView(mp_protectedView);
    }
}

void
JveGuiWindowableDock::slotViewTogglerTriggered(const bool toVisible)
{
    if (toVisible && mp_toggleWindowAction->isChecked()) {
        mp_toggleWindowAction->setChecked(false);
        mp_window->hide();
        attachViewToSelf();
    }
}

void
JveGuiWindowableDock::slotWindowTogglerTriggered(const bool toVisible)
{
    if (toVisible) {
        if (mp_toggleViewAction->isChecked()) {
            mp_toggleViewAction->trigger();
        }
        attachViewToWindow();
        mp_window->show();
    } else {
        mp_window->hide();
        attachViewToSelf();
    }
}

void
JveGuiWindowableDock::slotWindowClosedWithoutToggler(void)
{
    attachViewToSelf();
}


