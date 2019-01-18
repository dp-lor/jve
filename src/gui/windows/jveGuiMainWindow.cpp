

#include "jveGuiMainWindow.h"


#include <QEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMenuBar>


#include "../../core/definitions/jveDefines.h"
#include "../definitions/jveGuiAppearanceDefines.h"
#include "../definitions/jveGuiInteractiveDefines.h"
#include "../definitions/jveGuiWindowsSettingsDefines.h"


#include "../../core/definitions/jveOption.h"
#include "../../core/definitions/jveState.h"
#include "../../core/definitions/jveProjectState.h"

#include "../../core/signals/jveGlobalSignals.h"
#include "../../core/signals/jveProjectSignals.h"

#include "../../core/application/jveSettings.h"


jveGuiMainWindow::jveGuiMainWindow(void)
    : QMainWindow(Q_NULLPTR),
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

    // slot reject exit
    connect(
        &jveGlobalSignals,
        SIGNAL(wantRejectQuit()),
        this,
        SLOT(slotRejectExitSignalSent()),
        Qt::QueuedConnection
    );

    // slot set window title
    connect(
        &jveProjectSignals,
        SIGNAL(nameChanged(QString)),
        this,
        SLOT(slotSetWindowTitle(QString)),
        Qt::QueuedConnection
    );
    // slot project state changed
    connect(
        &jveProjectSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotProjectStateChanged(int)),
        Qt::QueuedConnection
    );

    // slot toggle status bar
    connect(
        &jveGlobalSignals,
        SIGNAL(wantToggleStatusBar(bool)),
        this,
        SLOT(slotToggleStatusBar(bool)),
        Qt::DirectConnection
    );
    // slot toggle fullscreen
    connect(
        &jveGlobalSignals,
        SIGNAL(wantToggleFullScreen(bool)),
        this,
        SLOT(slotToggleFullScreen(bool)),
        Qt::DirectConnection
    );
}

jveGuiMainWindow::~jveGuiMainWindow(void)
{
}

void
jveGuiMainWindow::changeEvent(QEvent *event)
{
    emit jveGlobalSignals.wantSendUiChangeEventType(event->type());
    QMainWindow::changeEvent(event);
}

void
jveGuiMainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (!mp_wantExitSignalSent) {
        mp_wantExitSignalSent = true;
        emit jveGlobalSignals.wantExit();
    }
}

void
jveGuiMainWindow::keyPressEvent(QKeyEvent* event)
{
    bool passToBase = false;

    //qDebug() << "key: " << event->key() << " mod: " << event->modifiers();
    if (event->isAutoRepeat()) {
        passToBase = true;
    } else {
        switch (event->key()) {
            case Qt::Key_Space:
                //emit jveGlobalSignals.wantTogglePlaying();
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

QList<jveGuiWindowableDock *> &
jveGuiMainWindow::windowableDocks(void)
{
    return mp_windowableDocks;
}

void
jveGuiMainWindow::restoreSettings(void)
{
    jveSettings.lock();

    if (jveSettings.contains(JVE_GUI_SETTINGS_MAIN_WINDOW_SHOW_STATUS_BAR)) {
        mp_statusBar.setVisible(
            jveSettings.value(
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

    if (jveSettings.contains(JVE_GUI_SETTINGS_MAIN_WINDOW_GEOMETRY)) {
        restoreGeometry(
            jveSettings.value(
                JVE_GUI_SETTINGS_MAIN_WINDOW_GEOMETRY
            ).toByteArray()
        );
    }
    if (jveSettings.contains(JVE_GUI_SETTINGS_MAIN_WINDOW_STATE)) {
        restoreState(
            jveSettings.value(
                JVE_GUI_SETTINGS_MAIN_WINDOW_STATE
            ).toByteArray()
        );
    }

    jveSettings.unlock();

    // docks visibility state
    foreach (jveGuiDock *dock, findChildren<jveGuiDock *>()) {
        dock->toggleTabifiedMode(0 < tabifiedDockWidgets(dock).size());
    }
    // status bar state
    emit jveGlobalSignals
            .wantSetUpStatusBarToggler(mp_statusBar.isVisible());
    // fullscreen state
    emit jveGlobalSignals
            .wantSetUpFullScreenToggler(isFullScreen());
}

void
jveGuiMainWindow::saveSettings(void)
{
    jveSettings.lock();

    jveSettings.setValue(
        JVE_GUI_SETTINGS_MAIN_WINDOW_SHOW_STATUS_BAR,
        mp_statusBar.isVisible()
    );
    jveSettings.setValue(
        JVE_GUI_SETTINGS_MAIN_WINDOW_GEOMETRY,
        saveGeometry()
    );
    jveSettings.setValue(
        JVE_GUI_SETTINGS_MAIN_WINDOW_STATE,
        saveState()
    );

    jveSettings.sync();
    jveSettings.unlock();
}

void
jveGuiMainWindow::clearStatusBarMessage(void)
{
    mp_statusBar.clearMessage();
}

void
jveGuiMainWindow::showStatusBarMessage(const QString &message)
{
    mp_statusBar.showMessage(
        message,
        JVE_GUI_STATUS_BAR_TIMEOUT * message.size()
    );
}

void
jveGuiMainWindow::slotRejectExitSignalSent(void)
{
    mp_wantExitSignalSent = false;
}

void
jveGuiMainWindow::slotProjectStateChanged(const int state)
{
    setWindowModified(state & jveProjectState::Modified);
}

void
jveGuiMainWindow::slotSetWindowTitle(const QString &title)
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
jveGuiMainWindow::slotToggleStatusBar(const bool enabled)
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
jveGuiMainWindow::slotToggleFullScreen(const bool enabled)
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


