

#include "JveApplicationThread.h"


#include "../definitions/JveOption.h"
#include "../utils/JveOptionsParser.h"

#include "../signals/JveGlobalSignals.h"
#include "../signals/JveProjectSignals.h"


JveApplicationThread::JveApplicationThread(void)
    : QThread(nullptr),
        mp_app()
{
    // move application to thread
    mp_app.moveToThread(this);

    // connect for self started
    connect(
        this,
        SIGNAL(started()),
        this,
        SLOT(slotRun()),
        Qt::DirectConnection
    );
}

JveApplicationThread::~JveApplicationThread(void)
{
}

void
JveApplicationThread::slotRun(void)
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


