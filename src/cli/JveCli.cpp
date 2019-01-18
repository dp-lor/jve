

#include "JveCli.h"


#include <QString>
#include <QCoreApplication>
#include <QDebug>


#include "../core/definitions/JveOption.h"
#include "../core/signals/JveGlobalSignals.h"
#include "../core/signals/JveProjectSignals.h"


#include "JveStdStreams.h"


JveCli::JveCli(void)
    : QObject(nullptr)
{
    // slot quit
    connect(
        &JveGlobalSignals,
        SIGNAL(wantAcceptQuit()),
        this,
        SLOT(slotQuitAccepted()),
        Qt::QueuedConnection
    );

    // slot state changed
    connect(
        &JveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotStateChanged(int)),
        Qt::QueuedConnection
    );

    // slot show report
    connect(
        &JveGlobalSignals,
        SIGNAL(wantShowReport(JveReport)),
        this,
        SLOT(slotShowReport(JveReport)),
        Qt::QueuedConnection
    );
}

JveCli::~JveCli(void)
{
}

void
JveCli::slotQuitAccepted(void)
{
    QCoreApplication::exit(0);
}

void
JveCli::slotStateChanged(const int state)
{
    Q_UNUSED(state);
}

void
JveCli::slotShowReport(const JveReport &report)
{
    switch (report.type()) {
        case JveReport::Error:
            JveStdErr
                << QString("%1 %2 - %3")
                       .arg(report.title())
                       .arg(report.subType(), 3, 10, QChar('0'))
                       .arg(report.message())
                << endl;
        break;
        case JveReport::Warning:
        case JveReport::Success:
            JveStdErr
                << QString("%1: %2")
                       .arg(report.title())
                       .arg(report.message())
                << endl;
        break;
        case JveReport::Info:
        case JveReport::Message:
            JveStdOut
                << report.message()
                << endl;
        break;
        default:
        break;
    }
}


