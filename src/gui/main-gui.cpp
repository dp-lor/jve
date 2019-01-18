

#include <QMetaType>
#include <QtGlobal>
#include <QApplication>
#include <QIcon>


#include "../core/definitions/JveDefines.h"
#include "../core/definitions/JveLocalizationDefines.h"
#include "../core/definitions/JveOption.h"
#include "definitions/JveGuiMediaDefines.h"

#include "../core/localization/JveLocalization.h"
#include "../core/structures/JveSourcesItemStruct.h"

#include "../core/utils/JveOptionsParser.h"
#include "../core/utils/JveXmlValidator.h"
#include "../core/application/JveReport.h"
#include "../core/signals/JveGlobalSignals.h"

#include "../core/application/JveApplicationThread.h"
#include "windows/JveGuiWindowManager.h"


int
main(int argc, char *argv[])
{
    // metatypes
    qRegisterMetaType
        <JveReport>("JveReport");
    qRegisterMetaType
        <JveSourcesItemStruct>("JveSourcesItemStruct");

    // Jve identificators
    QApplication::setOrganizationName  (JVE_ORG_NAME);
    QApplication::setOrganizationDomain(JVE_ORG_DOMAIN);
    QApplication::setApplicationName   (JVE_VERSION_STRING);
    QApplication::setApplicationVersion(JVE_VERSION_STRING);

    #if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
        // enable high dpi scaling
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    // qt app instance
    QApplication qtApp(argc, argv);

    // globally set icon for all windows
    QApplication::setWindowIcon(QIcon(JVE_GUI_ICON_JVE));

    // init localization
    JveLocalization.initForGui();

    // init user interface
    JveGuiWindowManager windowManager;
    // init main application thread
    JveApplicationThread appThread;

    try {

        // parse and store options (can be throw report inside)
        JveOptionsParser.parse(qtApp.arguments(), JveOption::None);
        // init required xml validator resources (can be throw report inside)
        JveXmlValidator.init();

        // populate user interface
        windowManager.populateGui();
        JveLocalization.emitLocaleChangedSignal();
        // run application event loop
        appThread.runApplication();

    } catch (const JveReport report) {
        // report here only when user interface is not populated
        emit JveGlobalSignals.wantShowReport(report);
    }

    //run main event loop
    int exitCode = qtApp.exec();

    // depopulate user interface
    windowManager.depopulateGui();

    // save settings
    JveLocalization.saveSettings();

    // shutdown
    appThread.quit();
    appThread.wait();

    return exitCode;
}


