

#include "JveGuiDockableWindow.h"


#include <QCloseEvent>
#include <QDataStream>


#include "../definitions/JveGuiAppearanceDefines.h"
#include "../../core/application/JveSettings.h"


JveGuiDockableWindow::JveGuiDockableWindow(
          QWidget *parent,
    const QString &visibleSettingsKey,
    const QString &geometrySettingsKey,
    const QString &extraSettingsKey
) : QWidget(parent, Qt::Window),
        // forced close flag
        mp_closeForced(false),
        // settings keys
        mp_visibleSettingsKey (visibleSettingsKey),
        mp_geometrySettingsKey(geometrySettingsKey),
        mp_extraSettingsKey   (extraSettingsKey),
        // settings
        mp_visible(false),
        mp_geometry(),
        mp_state(Qt::WindowNoState),
        // toggle action
        mp_toggleAction(new JveGuiAction(this)),
        // layout
        mp_layout(this)
{
    // properties
    setFocusPolicy(Qt::StrongFocus);
    setContextMenuPolicy(Qt::PreventContextMenu);
    setContentsMargins(
        JVE_GUI_MARGIN_SIZE,
        JVE_GUI_MARGIN_SIZE,
        JVE_GUI_MARGIN_SIZE,
        JVE_GUI_MARGIN_SIZE
    );

    // toggle action
    mp_toggleAction->setCheckable(true);

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);

    // initial read all settings
    readAllSettings();
}

JveGuiDockableWindow::~JveGuiDockableWindow(void)
{
}

void
JveGuiDockableWindow::closeEvent(QCloseEvent *event)
{
    if (mp_closeForced) {

        if (mp_visible) {
            updateSettingsForHide(true);
            saveAllSettings();
        }

        QWidget::closeEvent(event);

    } else {
        event->ignore();
        mp_toggleAction->setChecked(false);
        hide();
        emit closedWithoutToggler();
    }
}

QAction *
JveGuiDockableWindow::toggleAction(void)
{
    return mp_toggleAction;
}

bool
JveGuiDockableWindow::isVisibleBySettings(void) const
{
    return mp_visible;
}

void
JveGuiDockableWindow::fixVisibleBySettings(const bool isDockVisible)
{
    if (isDockVisible && mp_visible) {
        mp_visible = false;
    }
    mp_toggleAction->setChecked(mp_visible);
}

void
JveGuiDockableWindow::setForcedClosing(const bool forced)
{
    mp_closeForced = forced;
}

void
JveGuiDockableWindow::show(void)
{
    updateSettingsForShow();

    QWidget::show();

    restoreVisibleState();
    saveAllSettings();
}

void
JveGuiDockableWindow::hide(void)
{
    updateSettingsForHide();
    saveAllSettings();

    QWidget::hide();
}

void
JveGuiDockableWindow::attachView(QWidget *view)
{
    mp_layout.addWidget(view);
}

void
JveGuiDockableWindow::detachView(QWidget *view)
{
    mp_layout.removeWidget(view);
}

void
JveGuiDockableWindow::readAllSettings(void)
{
    JveSettings.lock();

    // visible
    if (JveSettings.contains(mp_visibleSettingsKey)) {
        mp_visible = JveSettings.value(mp_visibleSettingsKey).toBool();
    }

    // geometry
    if (JveSettings.contains(mp_geometrySettingsKey)) {
        mp_geometry = JveSettings.value(mp_geometrySettingsKey).toByteArray();
    }

    // extra
    if (JveSettings.contains(mp_extraSettingsKey)) {
        QByteArray  data = JveSettings.value(mp_extraSettingsKey).toByteArray();
        QDataStream stream(&data, QIODevice::ReadOnly);

        // state
        stream >> ( quint32 & ) mp_state;

        // TODO read screen number, viewport, workspace

        // fallback
        if (QDataStream::Ok != stream.status()) {
            // state
            mp_state = Qt::WindowNoState;

            // TODO set screen number, viewport, workspace from main window

        }
    }

    JveSettings.unlock();
}

void
JveGuiDockableWindow::restoreVisibleState(void)
{
    JveSettings.lock();

    // geometry
    restoreGeometry(mp_geometry);
    // state
    setWindowState(mp_state);

    // TODO restore screen number, viewport, workspace

    JveSettings.unlock();
}

void
JveGuiDockableWindow::updateSettingsForShow(void)
{
    mp_visible = true;

    // TODO validate and fix screen number, viewport, workspace
}

void
JveGuiDockableWindow::updateSettingsForHide(const bool forcedClosing)
{
    if (!forcedClosing) {
        mp_visible  = false;
    }

    mp_geometry = saveGeometry();
    mp_state    = (windowState() & ~Qt::WindowMinimized);

    // TODO set actual screen number, viewport, workspace
}

void
JveGuiDockableWindow::saveAllSettings(void)
{
    JveSettings.lock();

    // visible
    JveSettings.setValue(
        mp_visibleSettingsKey,
        mp_visible
    );
    // geometry
    JveSettings.setValue(
        mp_geometrySettingsKey,
        mp_geometry
    );

    // extra
    QByteArray  data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    // state
    stream << mp_state;

    // TODO (extra) save screen number, viewport, workspace

    JveSettings.setValue(mp_extraSettingsKey, data);

    JveSettings.sync();
    JveSettings.unlock();
}


