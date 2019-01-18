

#include "JveGuiMainWindow.h"


#include <QEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMenuBar>


#include "../../core/definitions/JveDefines.h"
#include "../definitions/JveGuiAppearanceDefines.h"
#include "../definitions/JveGuiInteractiveDefines.h"
#include "../definitions/JveGuiWindowsSettingsDefines.h"


#include "../../core/definitions/JveOption.h"
#include "../../core/definitions/JveState.h"

#include "../../core/signals/JveGlobalSignals.h"
#include "../../core/signals/JveProjectSignals.h"

#include "../../core/application/JveSettings.h"


JveGuiMainWindow::JveGuiMainWindow(void)
    : QMainWindow(nullptr),
        // boolean flags
        mp_wantExitSignalSent(false),
        mp_maximizedBeforeFullScreen(false),
        // conventional elements
        mp_menuFile(menuBar()),
        mp_menuEdit(menuBar()),
        mp_menuView(menuBar()),
        mp_menuWindow(menuBar()),
        mp_menuHelp(menuBar()),
        mp_menuLanguage(menuBar()),
        mp_statusBar(this),
        // windowable docks list
        mp_windowableDocks(),
        // docks
        mp_projectTreeDock(this),
        mp_projectSettingsDock(this),
        mp_videoMonitorDock(this),
        mp_projectSourcesDock(this),
        mp_historyDock(this)
{
    // properties
    setDockOptions(
        QMainWindow::AllowNestedDocks
            | QMainWindow::AllowTabbedDocks
    );
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
    setFocusPolicy(Qt::StrongFocus);
    setContextMenuPolicy(Qt::PreventContextMenu);

    // reset title
    slotSetWindowTitle("");


    /*** CONVENTIONAL ELEMENTS ********************************************/

    // main menu
    menuBar()->addAction( mp_menuFile     .menuAction() );
    menuBar()->addAction( mp_menuEdit     .menuAction() );
    menuBar()->addAction( mp_menuView     .menuAction() );
    menuBar()->addAction( mp_menuWindow   .menuAction() );
    menuBar()->addAction( mp_menuHelp     .menuAction() );
    menuBar()->addAction( mp_menuLanguage .menuAction() );

    // status bar
    mp_statusBar.setSizeGripEnabled(false);
    setStatusBar(&mp_statusBar);


    /*** DOCKS ************************************************************/

    // project tree
    addDockWidget(Qt::LeftDockWidgetArea, &mp_projectTreeDock);
    // video monitor
    addDockWidget(Qt::RightDockWidgetArea, &mp_videoMonitorDock);
    mp_windowableDocks.append(&mp_videoMonitorDock);
    // project settings
    addDockWidget(Qt::RightDockWidgetArea, &mp_projectSettingsDock);
    mp_windowableDocks.append(&mp_projectSettingsDock);
    // project sources
    addDockWidget(Qt::RightDockWidgetArea, &mp_projectSourcesDock);
    mp_windowableDocks.append(&mp_projectSourcesDock);

    // history
    addDockWidget(Qt::RightDockWidgetArea, &mp_historyDock);
    mp_windowableDocks.append(&mp_historyDock);

    // default docks tabbing
    tabifyDockWidget(&mp_projectSettingsDock, &mp_projectSourcesDock);
    tabifyDockWidget(&mp_projectSourcesDock, &mp_historyDock);

    // default raised tabified dock
    mp_projectSourcesDock.raise();


    /*** SETUP VIEW MENU **************************************************/

    // transport bar menu
    mp_menuView.addTransportBarFeatures();
    // separator
    mp_menuView.addSeparator();
    // ruler features
    mp_menuView.addRulerFeatures();
    // separator
    mp_menuView.addSeparator();
    // project settings dock toggler
    mp_menuView.addAction(mp_projectSettingsDock.toggleViewAction());
    // video monitor dock toggler
    mp_menuView.addAction(mp_videoMonitorDock.toggleViewAction());
    // project sources dock toggler
    mp_menuView.addAction(mp_projectSourcesDock.toggleViewAction());
    // history dock toggler
    mp_menuView.addAction(mp_historyDock.toggleViewAction());
    // separator
    mp_menuView.addSeparator();
    // status bar toggler
    mp_menuView.addToggleStatusBarAction();
    // separator
    mp_menuView.addSeparator();
    // full screen toggler
    mp_menuView.addToggleFullScreenAction();


    /*** SETUP WINDOW MENU ************************************************/

    // project settings window toggler
    mp_menuWindow.addAction(mp_projectSettingsDock.toggleWindowAction());
    // video monitor window toggler
    mp_menuWindow.addAction(mp_videoMonitorDock.toggleWindowAction());
    // project sources window toggler
    mp_menuWindow.addAction(mp_projectSourcesDock.toggleWindowAction());
    // history window toggler
    mp_menuWindow.addAction(mp_historyDock.toggleWindowAction());


    /*** SIGNALS AND SLOTS ************************************************/

    // slot state changed
    connect(
        &JveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotStateChanged(int)),
        Qt::QueuedConnection
    );

    // slot reject exit
    connect(
        &JveGlobalSignals,
        SIGNAL(wantRejectQuit()),
        this,
        SLOT(slotRejectExitSignalSent()),
        Qt::QueuedConnection
    );

    // slot set window title
    connect(
        &JveProjectSignals,
        SIGNAL(nameChanged(QString)),
        this,
        SLOT(slotSetWindowTitle(QString)),
        Qt::QueuedConnection
    );

    // slot toggle status bar
    connect(
        &JveGlobalSignals,
        SIGNAL(wantToggleStatusBar(bool)),
        this,
        SLOT(slotToggleStatusBar(bool)),
        Qt::DirectConnection
    );
    // slot toggle fullscreen
    connect(
        &JveGlobalSignals,
        SIGNAL(wantToggleFullScreen(bool)),
        this,
        SLOT(slotToggleFullScreen(bool)),
        Qt::DirectConnection
    );
}

JveGuiMainWindow::~JveGuiMainWindow(void)
{
}

void
JveGuiMainWindow::changeEvent(QEvent *event)
{
    emit JveGlobalSignals.wantSendUiChangeEventType(event->type());
    QMainWindow::changeEvent(event);
}

void
JveGuiMainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (!mp_wantExitSignalSent) {
        mp_wantExitSignalSent = true;
        emit JveGlobalSignals.wantExit();
    }
}

void
JveGuiMainWindow::keyPressEvent(QKeyEvent* event)
{
    bool passToBase = false;

    //qDebug() << "key: " << event->key() << " mod: " << event->modifiers();
    if (event->isAutoRepeat()) {
        passToBase = true;
    } else {
        switch (event->key()) {
            case Qt::Key_Space:
                //emit JveGlobalSignals.wantTogglePlaying();
            break;
            default:
                passToBase = true;
            break;
        }
    }

    if (passToBase) {
        QMainWindow::keyPressEvent(event);
    } else {
        event->ignore();
    }
}

QList<JveGuiWindowableDock *> &
JveGuiMainWindow::windowableDocks(void)
{
    return mp_windowableDocks;
}

void
JveGuiMainWindow::restoreSettings(void)
{
    JveSettings.lock();

    if (JveSettings.contains(JVE_GUI_SETTINGS_MAIN_WINDOW_SHOW_STATUS_BAR)) {
        mp_statusBar.setVisible(
            JveSettings.value(
                JVE_GUI_SETTINGS_MAIN_WINDOW_SHOW_STATUS_BAR
            ).toBool()
        );
    }
    if (!mp_statusBar.isHidden()) {
        setContentsMargins(
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE,
            0
        );
    } else {
        setContentsMargins(
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE
        );
    }

    if (JveSettings.contains(JVE_GUI_SETTINGS_MAIN_WINDOW_GEOMETRY)) {
        restoreGeometry(
            JveSettings.value(
                JVE_GUI_SETTINGS_MAIN_WINDOW_GEOMETRY
            ).toByteArray()
        );
    }
    if (JveSettings.contains(JVE_GUI_SETTINGS_MAIN_WINDOW_STATE)) {
        restoreState(
            JveSettings.value(
                JVE_GUI_SETTINGS_MAIN_WINDOW_STATE
            ).toByteArray()
        );
    }

    JveSettings.unlock();

    // docks visibility state
    foreach (JveGuiDock *dock, findChildren<JveGuiDock *>()) {
        dock->toggleTabifiedMode(0 < tabifiedDockWidgets(dock).size());
    }
    // status bar state
    emit JveGlobalSignals
            .wantSetUpStatusBarToggler(mp_statusBar.isVisible());
    // fullscreen state
    emit JveGlobalSignals
            .wantSetUpFullScreenToggler(isFullScreen());
}

void
JveGuiMainWindow::saveSettings(void)
{
    JveSettings.lock();

    JveSettings.setValue(
        JVE_GUI_SETTINGS_MAIN_WINDOW_SHOW_STATUS_BAR,
        mp_statusBar.isVisible()
    );
    JveSettings.setValue(
        JVE_GUI_SETTINGS_MAIN_WINDOW_GEOMETRY,
        saveGeometry()
    );
    JveSettings.setValue(
        JVE_GUI_SETTINGS_MAIN_WINDOW_STATE,
        saveState()
    );

    JveSettings.sync();
    JveSettings.unlock();
}

void
JveGuiMainWindow::clearStatusBarMessage(void)
{
    mp_statusBar.clearMessage();
}

void
JveGuiMainWindow::showStatusBarMessage(const QString &message)
{
    mp_statusBar.showMessage(
        message,
        JVE_GUI_STATUS_BAR_TIMEOUT * message.size()
    );
}

void
JveGuiMainWindow::slotStateChanged(const int state)
{
    setWindowModified(state & JveState::ProjectModified);
}

void
JveGuiMainWindow::slotRejectExitSignalSent(void)
{
    mp_wantExitSignalSent = false;
}

void
JveGuiMainWindow::slotSetWindowTitle(const QString &title)
{
    QString fullTitle("[*]");

    if (!title.isEmpty()) {
        fullTitle
            .append(title)
            .append(" - ");
    }
    fullTitle.append(JVE_NAME_STRING);

    QMainWindow::setWindowTitle(fullTitle);
}

void
JveGuiMainWindow::slotToggleStatusBar(const bool enabled)
{
    if (enabled) {
        setContentsMargins(
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE,
            0
        );
        mp_statusBar.setVisible(true);
    } else {
        setContentsMargins(
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE,
            JVE_GUI_MARGIN_SIZE
        );
        mp_statusBar.setVisible(false);
    }
}

void
JveGuiMainWindow::slotToggleFullScreen(const bool enabled)
{
    if (enabled) {
        mp_maximizedBeforeFullScreen = isMaximized();
        showFullScreen();
    } else {
        mp_maximizedBeforeFullScreen
            ? showMaximized()
            : showNormal();
    }
}


