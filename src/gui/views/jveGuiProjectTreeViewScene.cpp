

#include "jveGuiProjectTreeViewScene.h"


#include <QByteArray>
#include <QDataStream>


#include "../../core/application/jveSettings.h"
#include "../../core/signals/jveGlobalSignals.h"

#include "../definitions/jveGuiSettingsDefines.h"
#include "../definitions/jveGuiRulerType.h"


#include "project-tree/jveGuiPTRegion.h"


jveGuiProjectTreeViewScene::jveGuiProjectTreeViewScene(QObject *parent)
    : QGraphicsScene(parent),
        mp_rulerEnabled(false),
        mp_rulerType(jveGuiRulerType::None)
{
    // test now
    jveGuiPTRegion *l1 = new jveGuiPTRegion(300, 0, Q_NULLPTR);
    jveGuiPTRegion *l2 = new jveGuiPTRegion(100, 20, l1);
    jveGuiPTRegion *l3 = new jveGuiPTRegion(60, 220, l1);
    addItem(l1);

    Q_UNUSED(l2);
    Q_UNUSED(l3);

    // initial state
    restoreSettings();

    // slot toggle ruler
    connect(
        &jveGlobalSignals,
        SIGNAL(wantToggleRuler(bool)),
        this,
        SLOT(slotToggleRuler(bool)),
        Qt::DirectConnection
    );
    // slot set ruler type
    connect(
        &jveGlobalSignals,
        SIGNAL(wantSetRulerType(int)),
        this,
        SLOT(slotSetRulerType(int)),
        Qt::DirectConnection
    );
}

jveGuiProjectTreeViewScene::~jveGuiProjectTreeViewScene(void)
{
    saveSettings();
}

inline void
jveGuiProjectTreeViewScene::restoreSettings(void)
{
    jveSettings.lock();

    bool       contains     = false;
    bool       setDefaults  = false;
    QByteArray state;
    bool       rulerEnabled = true;
    int        rulerType    = jveGuiRulerType::TimeAndFrames;

    contains = jveSettings.contains(
        JVE_GUI_SETTINGS_PROJECT_TREE_VIEW_SCENE_STATE
    );
    if (contains) {
        state = jveSettings.value(
            JVE_GUI_SETTINGS_PROJECT_TREE_VIEW_SCENE_STATE
        ).toByteArray();
    }
    if (!state.isEmpty()) {
        QDataStream stream(&state, QIODevice::ReadOnly);
        stream >> rulerEnabled;
        stream >> rulerType;
        if (
            QDataStream::Ok != stream.status()
                || (
                    jveGuiRulerType::Time > rulerType
                        && jveGuiRulerType::TimeAndFrames < rulerType
                )
        ) {
            setDefaults = true;
        }
    }
    if (setDefaults) {
        // NOTE rulerEnabled is boolean and not required reset
        rulerType = jveGuiRulerType::TimeAndFrames;
    }

    jveSettings.unlock();

    slotToggleRuler(rulerEnabled);
    slotSetRulerType(rulerType);

    emit jveGlobalSignals.wantSetUpRulerFeatures(rulerEnabled, rulerType);
}

inline void
jveGuiProjectTreeViewScene::saveSettings(void)
{
    jveSettings.lock();

    QByteArray  state;
    QDataStream stream(&state, QIODevice::WriteOnly);

    stream << mp_rulerEnabled;
    stream << mp_rulerType;
    jveSettings.setValue(
        JVE_GUI_SETTINGS_PROJECT_TREE_VIEW_SCENE_STATE,
        state
    );

    jveSettings.sync();
    jveSettings.unlock();
}

void
jveGuiProjectTreeViewScene::slotToggleRuler(const bool status)
{
    mp_rulerEnabled = status;
}

void
jveGuiProjectTreeViewScene::slotSetRulerType(const int type)
{
    mp_rulerType = type;
}


