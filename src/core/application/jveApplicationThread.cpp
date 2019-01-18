

#include "jveApplicationThread.h"


#include "../definitions/jveOption.h"
#include "../utils/jveOptionsParser.h"

#include "../signals/jveGlobalSignals.h"
#include "../signals/jveProjectSignals.h"


jveApplicationThread::jveApplicationThread(void)
    : QThread(Q_NULLPTR),
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

jveApplicationThread::~jveApplicationThread(void)
{
}

void
jveApplicationThread::runApplication(void)
{
    start(QThread::HighPriority);
}

void
jveApplicationThread::slotRunByOptions(void)
{
    int options = jveOptionsParser.options();

    // load project
    if (options & jveOption::LoadProject) {
        emit jveProjectSignals
                .wantLoadProject(jveOptionsParser.projectFilePath());
    }
    // render project
    if (options & jveOption::RenderProject) {
        emit jveProjectSignals.wantRenderProject();
    }
    // quit
    if (options & jveOption::Quit) {
        emit jveGlobalSignals.wantAcceptQuit();
    }
}


