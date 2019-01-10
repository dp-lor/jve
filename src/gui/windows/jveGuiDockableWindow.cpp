

#include "jveGuiDockableWindow.h"


#include <QHideEvent>
#include <QCloseEvent>
#include <QAction>
#include <QByteArray>
#include <QDataStream>


#include "../definitions/jveGuiAppearanceDefines.h"


#include "../../core/application/jveSettings.h"


jveGuiDockableWindow::jveGuiDockableWindow(
          QWidget *parent,
    const QString &geometrySettingsKey,
    const QString &stateSettingsKey,
    const QString &extraSettingsKey
) : QWidget(parent, Qt::Window),
        // flags
        mp_forcedClosing(false),
        mp_isVisibleFromSettings(false),
        // settings keys
        mp_geometrySettingsKey(geometrySettingsKey),
        mp_stateSettingsKey   (stateSettingsKey),
        mp_extraSettingsKey   (extraSettingsKey),
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
    mp_toggleAction = new QAction(this);
    mp_toggleAction->setAutoRepeat(false);
    mp_toggleAction->setCheckable(true);

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);

    // initial restore settings
    restoreSettings();
}

jveGuiDockableWindow::~jveGuiDockableWindow(void)
{
}

void
jveGuiDockableWindow::showEvent(QShowEvent *event)
{
    restoreSettings();
    QWidget::showEvent(event);
}

void
jveGuiDockableWindow::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
    if (!mp_forcedClosing) {
        saveSettings();
    }
}

void
jveGuiDockableWindow::closeEvent(QCloseEvent *event)
{
    if (mp_forcedClosing) {
        QWidget::closeEvent(event);
    } else {
        event->ignore();
        mp_toggleAction->setChecked(false);
        setVisible(false);
        emit closedWithoutToggler();
    }
}

QAction *
jveGuiDockableWindow::toggleAction(void)
{
    return mp_toggleAction;
}

bool
jveGuiDockableWindow::isVisibleFromSettings(void) const
{
    return mp_isVisibleFromSettings;
}

void
jveGuiDockableWindow::fixVisibilityState(const bool isDockVisible)
{
    if (isDockVisible && mp_isVisibleFromSettings) {
        mp_isVisibleFromSettings = false;
    }
    mp_toggleAction->setChecked(mp_isVisibleFromSettings);
}

void
jveGuiDockableWindow::setForcedClosing(const bool state)
{
    mp_forcedClosing = state;
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
jveGuiDockableWindow::restoreSettings(void)
{
    jveSettings.lock();

    if (jveSettings.contains(mp_geometrySettingsKey)) {
        restoreGeometry(
            jveSettings.value(mp_geometrySettingsKey).toByteArray()
        );
    }
    if (jveSettings.contains(mp_stateSettingsKey)) {
        restoreState(jveSettings.value(mp_stateSettingsKey).toByteArray());
    }
    if (jveSettings.contains(mp_extraSettingsKey)) {
        restoreExtra(jveSettings.value(mp_extraSettingsKey).toByteArray());
    }

    jveSettings.unlock();
}

void
jveGuiDockableWindow::saveSettings(void)
{
    jveSettings.lock();

    // geometry
    jveSettings.setValue(mp_geometrySettingsKey, saveGeometry());
    // state
    jveSettings.setValue(mp_stateSettingsKey, saveState());

    // extra
    mp_isVisibleFromSettings = isVisible();

    jveSettings.setValue(mp_extraSettingsKey, saveExtra());

    jveSettings.sync();
    jveSettings.unlock();
}

void
jveGuiDockableWindow::restoreState(const QByteArray &state)
{
    QByteArray       readingState = state;
    QDataStream      stream(&readingState, QIODevice::ReadOnly);
    Qt::WindowStates stateValue;

    stream >> ( quint32 & ) stateValue;
    setWindowState(
        QDataStream::Ok == stream.status()
            ? stateValue
            : Qt::WindowNoState
    );
}

QByteArray
jveGuiDockableWindow::saveState(void) const
{
    QByteArray  state;
    QDataStream stream(&state, QIODevice::WriteOnly);

    stream << (windowState() & ~Qt::WindowMinimized);

    return state;
}

void
jveGuiDockableWindow::restoreExtra(const QByteArray &data)
{
    QByteArray  readingData = data;
    QDataStream stream(&readingData, QIODevice::ReadOnly);

    stream >> mp_isVisibleFromSettings;

    if (QDataStream::Ok != stream.status()) {
        mp_isVisibleFromSettings = false;
    }
}

QByteArray
jveGuiDockableWindow::saveExtra(void) const
{
    QByteArray  data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << mp_isVisibleFromSettings;

    return data;
}


