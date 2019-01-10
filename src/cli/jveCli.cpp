

#include "jveCli.h"


#include <QString>
#include <QCoreApplication>
#include <QDebug>


#include "../core/definitions/jveOption.h"
#include "../core/signals/jveGlobalSignals.h"
#include "../core/signals/jveProjectSignals.h"


#include "jveStdStreams.h"


jveCli::jveCli(void)
    : QObject(Q_NULLPTR)
{
    // slot quit
    connect(
        &jveGlobalSignals,
        SIGNAL(wantAcceptQuit()),
        this,
        SLOT(slotQuitAccepted()),
        Qt::QueuedConnection
    );

    // slot state changed
    connect(
        &jveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotStateChanged(int)),
        Qt::QueuedConnection
    );

    // slot show report
    connect(
        &jveGlobalSignals,
        SIGNAL(wantShowReport(jveReport)),
        this,
        SLOT(slotShowReport(jveReport)),
        Qt::QueuedConnection
    );
}

jveCli::~jveCli(void)
{
}

void
jveCli::slotQuitAccepted(void)
{
    QCoreApplication::exit(0);
}

void
jveCli::slotStateChanged(const int state)
{
    Q_UNUSED(state);
}

void
jveCli::slotShowReport(const jveReport &report)
{
    switch (report.type()) {
        case jveReport::Error:
            jveStdErr
                << QString("%1 %2 - %3")
                       .arg(report.title())
                       .arg(report.subType(), 3, 10, QChar('0'))
                       .arg(report.message())
                << endl;
        break;
        case jveReport::Warning:
        case jveReport::Success:
            jveStdErr
                << QString("%1: %2")
                       .arg(report.title())
                       .arg(report.message())
                << endl;
        break;
        case jveReport::Info:
        case jveReport::Message:
            jveStdOut
                << report.message()
                << endl;
        break;
        default:
        break;
    }
}


