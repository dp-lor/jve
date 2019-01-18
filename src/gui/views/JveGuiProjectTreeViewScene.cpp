

#include "JveGuiProjectTreeViewScene.h"


#include <QByteArray>
#include <QDataStream>


#include "../../core/application/JveSettings.h"
#include "../../core/signals/JveGlobalSignals.h"

#include "../definitions/JveGuiSettingsDefines.h"
#include "../definitions/JveGuiRulerType.h"


#include "project-tree/JveGuiPTRegion.h"


JveGuiProjectTreeViewScene::JveGuiProjectTreeViewScene(QObject *parent)
    : QGraphicsScene(parent),
        mp_rulerEnabled(false),
        mp_rulerType(JveGuiRulerType::None)
{
    // test now
    JveGuiPTRegion *l1 = new JveGuiPTRegion(300, 0, nullptr);
    JveGuiPTRegion *l2 = new JveGuiPTRegion(100, 20, l1);
    JveGuiPTRegion *l3 = new JveGuiPTRegion(60, 220, l1);
    addItem(l1);

    Q_UNUSED(l2);
    Q_UNUSED(l3);

    // initial state
    restoreSettings();

    // slot toggle ruler
    connect(
        &JveGlobalSignals,
        SIGNAL(wantToggleRuler(bool)),
        this,
        SLOT(slotToggleRuler(bool)),
        Qt::DirectConnection
    );
    // slot set ruler type
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSetRulerType(int)),
        this,
        SLOT(slotSetRulerType(int)),
        Qt::DirectConnection
    );
}

JveGuiProjectTreeViewScene::~JveGuiProjectTreeViewScene(void)
{
    saveSettings();
}

inline void
JveGuiProjectTreeViewScene::restoreSettings(void)
{
    JveSettings.lock();

    bool       contains     = false;
    bool       setDefaults  = false;
    QByteArray state;
    bool       rulerEnabled = true;
    int        rulerType    = JveGuiRulerType::TimeAndFrames;

    contains = JveSettings.contains(
        JVE_GUI_SETTINGS_PROJECT_TREE_VIEW_SCENE_STATE
    );
    if (contains) {
        state = JveSettings.value(
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
                    JveGuiRulerType::Time > rulerType
                        && JveGuiRulerType::TimeAndFrames < rulerType
                )
        ) {
            setDefaults = true;
        }
    }
    if (setDefaults) {
        // NOTE rulerEnabled is boolean and not required reset
        rulerType = JveGuiRulerType::TimeAndFrames;
    }

    JveSettings.unlock();

    slotToggleRuler(rulerEnabled);
    slotSetRulerType(rulerType);

    emit JveGlobalSignals.wantSetUpRulerFeatures(rulerEnabled, rulerType);
}

inline void
JveGuiProjectTreeViewScene::saveSettings(void)
{
    JveSettings.lock();

    QByteArray  state;
    QDataStream stream(&state, QIODevice::WriteOnly);

    stream << mp_rulerEnabled;
    stream << mp_rulerType;
    JveSettings.setValue(
        JVE_GUI_SETTINGS_PROJECT_TREE_VIEW_SCENE_STATE,
        state
    );

    JveSettings.sync();
    JveSettings.unlock();
}

void
JveGuiProjectTreeViewScene::slotToggleRuler(const bool status)
{
    mp_rulerEnabled = status;
}

void
JveGuiProjectTreeViewScene::slotSetRulerType(const int type)
{
    mp_rulerType = type;
}


