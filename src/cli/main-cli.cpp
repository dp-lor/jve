

#include <QMetaType>
#include <QCoreApplication>


#include "../core/definitions/jveDefines.h"
#include "../core/definitions/jveLocalizationDefines.h"
#include "../core/definitions/jveOption.h"

#include "../core/localization/jveLocalization.h"

#include "../core/utils/jveOptionsParser.h"
#include "../core/utils/jveXmlValidator.h"
#include "../core/application/jveReport.h"
#include "../core/signals/jveGlobalSignals.h"

#include "../core/application/jveApplicationThread.h"
#include "jveCli.h"


int
main(int argc, char *argv[])
{
    // report metatype
    qRegisterMetaType<jveReport>("jveReport");

    // jve identificators
    QCoreApplication::setOrganizationName  (JVE_ORG_NAME);
    QCoreApplication::setOrganizationDomain(JVE_ORG_DOMAIN);
    QCoreApplication::setApplicationName   (JVE_VERSION_STRING);
    QCoreApplication::setApplicationVersion(JVE_VERSION_STRING);

    // qt app instance
    QCoreApplication qtApp(argc, argv);

    // init localization
    jveLocalization.initForCli();

    // init command line interface
    jveCli mainCli;
    // init main application thread
    jveApplicationThread appThread;

    try {

        // parse and store options (can be throw report inside)
        jveOptionsParser.parse(
            qtApp.arguments(),
            jveOption::NonGui | jveOption::Quit
        );
        // init required xml validator resources (can be throw inside)
        jveXmlValidator.init();

        // run application event loop
        appThread.runApplication();

    } catch (const jveReport report) {
        // report here only when user interface is not populated
        emit jveGlobalSignals.wantShowReport(report);
        emit jveGlobalSignals.wantAcceptQuit();
    }

    //run main event loop
    int exitCode = qtApp.exec();

    // shutdown
    appThread.quit();
    appThread.wait();

    return exitCode;
}


