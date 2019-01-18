

#include "jveGuiDockableWindow.h"


#include <QCloseEvent>
#include <QDataStream>


#include "../definitions/jveGuiAppearanceDefines.h"
#include "../../core/application/jveSettings.h"


jveGuiDockableWindow::jveGuiDockableWindow(
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
        mp_toggleAction(new jveGuiAction(this)),
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

jveGuiDockableWindow::~jveGuiDockableWindow(void)
{
}

void
jveGuiDockableWindow::closeEvent(QCloseEvent *event)
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
jveGuiDockableWindow::toggleAction(void)
{
    return mp_toggleAction;
}

bool
jveGuiDockableWindow::isVisibleBySettings(void) const
{
    return mp_visible;
}

void
jveGuiDockableWindow::fixVisibleBySettings(const bool isDockVisible)
{
    if (isDockVisible && mp_visible) {
        mp_visible = false;
    }
    mp_toggleAction->setChecked(mp_visible);
}

void
jveGuiDockableWindow::setForcedClosing(const bool forced)
{
    mp_closeForced = forced;
}

void
jveGuiDockableWindow::show(void)
{
    updateSettingsForShow();

    QWidget::show();

    restoreVisibleState();
    saveAllSettings();
}

void
jveGuiDockableWindow::hide(void)
{
    updateSettingsForHide();
    saveAllSettings();

    QWidget::hide();
}

void
jveGuiDockableWindow::attachView(QWidget *view)
{
    mp_layout.addWidget(view);
}

void
jveGuiDockableWindow::detachView(QWidget *view)
{
    mp_layout.removeWidget(view);
}

void
jveGuiDockableWindow::readAllSettings(void)
{
    jveSettings.lock();

    // visible
    if (jveSettings.contains(mp_visibleSettingsKey)) {
        mp_visible = jveSettings.value(mp_visibleSettingsKey).toBool();
    }

    // geometry
    if (jveSettings.contains(mp_geometrySettingsKey)) {
        mp_geometry = jveSettings.value(mp_geometrySettingsKey).toByteArray();
    }

    // extra
    if (jveSettings.contains(mp_extraSettingsKey)) {
        QByteArray  data = jveSettings.value(mp_extraSettingsKey).toByteArray();
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

    jveSettings.unlock();
}

void
jveGuiDockableWindow::restoreVisibleState(void)
{
    jveSettings.lock();

    // geometry
    restoreGeometry(mp_geometry);
    // state
    setWindowState(mp_state);

    // TODO restore screen number, viewport, workspace

    jveSettings.unlock();
}

void
jveGuiDockableWindow::updateSettingsForShow(void)
{
    mp_visible = true;

    // TODO validate and fix screen number, viewport, workspace
}

void
jveGuiDockableWindow::updateSettingsForHide(const bool forcedClosing)
{
    if (!forcedClosing) {
        mp_visible  = false;
    }

    mp_geometry = saveGeometry();
    mp_state    = (windowState() & ~Qt::WindowMinimized);

    // TODO set actual screen number, viewport, workspace
}

void
jveGuiDockableWindow::saveAllSettings(void)
{
    jveSettings.lock();

    // visible
    jveSettings.setValue(
        mp_visibleSettingsKey,
        mp_visible
    );
    // geometry
    jveSettings.setValue(
        mp_geometrySettingsKey,
        mp_geometry
    );

    // extra
    QByteArray  data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    // state
    stream << mp_state;

    // TODO (extra) save screen number, viewport, workspace

    jveSettings.setValue(mp_extraSettingsKey, data);

    jveSettings.sync();
    jveSettings.unlock();
}


