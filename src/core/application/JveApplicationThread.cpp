

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
        SLOT(slotRunByOptions())
    );
}

JveApplicationThread::~JveApplicationThread(void)
{
}

void
JveApplicationThread::runApplication(void)
{
    start(QThread::HighPriority);
}

void
JveApplicationThread::slotRunByOptions(void)
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


