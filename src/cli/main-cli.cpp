

#include <QMetaType>
#include <QCoreApplication>


#include "../core/definitions/JveDefines.h"
#include "../core/definitions/JveLocalizationDefines.h"
#include "../core/definitions/JveOption.h"

#include "../core/localization/JveLocalization.h"
#include "../core/structures/JveSourcesItemStruct.h"

#include "../core/utils/JveOptionsParser.h"
#include "../core/utils/JveXmlValidator.h"
#include "../core/application/JveReport.h"
#include "../core/signals/JveGlobalSignals.h"

#include "../core/application/JveThreadPool.h"
#include "JveCli.h"


int
main(int argc, char *argv[])
{
    // report metatype
    qRegisterMetaType
        <JveReport>("JveReport");
    qRegisterMetaType
        <JveSourcesItemStruct>("JveSourcesItemStruct");

    // Jve identificators
    QCoreApplication::setOrganizationName  (JVE_ORG_NAME);
    QCoreApplication::setOrganizationDomain(JVE_ORG_DOMAIN);
    QCoreApplication::setApplicationName   (JVE_VERSION_STRING);
    QCoreApplication::setApplicationVersion(JVE_VERSION_STRING);

    // qt app instance
    QCoreApplication qtApp(argc, argv);

    // init localization
    JveLocalization.initForCli();

    // init command line interface
    JveCli mainCli;
    // init threadpool
    JveThreadPool threadPool;

    try {

        // parse and store options (can be throw report inside)
        JveOptionsParser.parse(
            qtApp.arguments(),
            JveOption::NonGui | JveOption::Quit
        );
        // init required xml validator resources (can be throw inside)
        JveXmlValidator.init();

        // start jve threads
        threadPool.startThreads();

    } catch (const JveReport report) {
        // report here only when user interface is not populated
        emit JveGlobalSignals.wantShowReport(report);
        emit JveGlobalSignals.wantAcceptQuit();
    }

    //run main event loop
    int exitCode = qtApp.exec();

    // stop all jve threads
    threadPool.stopThreads();

    return exitCode;
}


