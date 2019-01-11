

#include <QMetaType>
#include <QtGlobal>
#include <QApplication>
#include <QIcon>


#include "../core/definitions/jveDefines.h"
#include "definitions/jveGuiMediaDefines.h"
#include "../core/definitions/jveLocalizationDefines.h"
#include "../core/definitions/jveOption.h"

#include "../core/localization/jveLocalization.h"

#include "../core/structures/jveSourcesItemStruct.h"

#include "../core/utils/jveOptionsParser.h"
#include "../core/utils/jveXmlValidator.h"
#include "../core/application/jveReport.h"

#include "../core/signals/jveGlobalSignals.h"

#include "../core/application/jveApplicationThread.h"
#include "windows/jveGuiWindowManager.h"


int
main(int argc, char *argv[])
{
    // metatypes
    qRegisterMetaType
        <jveReport>("jveReport");
    qRegisterMetaType
        <jveSourcesItemStruct>("jveSourcesItemStruct");

    // jve identificators
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
    jveLocalization.initForGui();

    // init user interface
    jveGuiWindowManager windowManager;
    // init main application thread
    jveApplicationThread appThread;

    try {

        // parse and store options (can be throw report inside)
        jveOptionsParser.parse(qtApp.arguments(), jveOption::None);
        // init required xml validator resources (can be throw report inside)
        jveXmlValidator.init();

        // populate user interface
        windowManager.populateGui();
        jveLocalization.emitLocaleChangedSignal();
        // run application event loop
        appThread.runApplication();

    } catch (const jveReport report) {
        // report here only when user interface is not populated
        emit jveGlobalSignals.wantShowReport(report);
    }

    //run main event loop
    int exitCode = qtApp.exec();

    // depopulate user interface
    windowManager.depopulateGui();

    // save settings
    jveLocalization.saveSettings();

    // shutdown
    appThread.quit();
    appThread.wait();

    return exitCode;
}


