

#include "JveMainThread.h"


#include "../definitions/JveOption.h"
#include "../utils/JveOptionsParser.h"

#include "../signals/JveGlobalSignals.h"
#include "../signals/JveProjectSignals.h"


JveMainThread::JveMainThread(void)
    : QThread(nullptr),
        mp_controller()
{
    // move controller to thread
    mp_controller.moveToThread(this);

    // connect for self started
    connect(
        this,
        SIGNAL(started()),
        this,
        SLOT(slotRun()),
        Qt::DirectConnection
    );
}

JveMainThread::~JveMainThread(void)
{
}

void
JveMainThread::slotRun(void)
{
    int options = JveOptionsParser.options();

    // load project
    if (options & JveOption::LoadProject) {
        emit JveProjectSignals
                .wantLoadProject(JveOptionsParser.projectFilePath());
    }
    // render project
    if (options & JveOption::RenderProject) {
        emit JveProjectSignals.wantRenderProject();
    }
    // quit
    if (options & JveOption::Quit) {
        emit JveGlobalSignals.wantAcceptQuit();
    }
}


