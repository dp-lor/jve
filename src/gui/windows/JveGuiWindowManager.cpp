

#include "JveGuiWindowManager.h"


#include <QList>
#include <QApplication>
#include <QPointer>
#include <QStringList>


#include "../../core/definitions/JveOption.h"
#include "../../core/definitions/JveState.h"

#include "../../core/signals/JveGlobalSignals.h"
#include "../../core/signals/JveProjectSignals.h"
#include "../../core/signals/JveProjectSourcesSignals.h"

#include "../../core/mutexes/JveLoadingProjectMutex.h"
#include "../../core/application/Jve.h"

#include "../dialogs/JveGuiLoadingProjectProgressDialod.h"
#include "../dialogs/JveGuiReportBox.h"
#include "../dialogs/JveGuiOpenProjectDialog.h"
#include "../dialogs/JveGuiSaveProjectDialog.h"
#include "../dialogs/JveGuiModifiedProjectWarning.h"
#include "../dialogs/JveGuiAddProjectSourcesMediaItemsDialog.h"
#include "../dialogs/JveGuiAddProjectSourcesImagesSequenceItemDialog.h"
#include "../dialogs/JveGuiProjectSourcesItemPropertiesDialog.h"
#include "../dialogs/JveGuiPreferencesDialog.h"
#include "../dialogs/JveGuiKeyboardShortcutsInfo.h"
#include "../dialogs/JveGuiAboutJveBox.h"

#include "JveGuiMainWindow.h"
#include "../docks/JveGuiWindowableDock.h"


JveGuiWindowManager::JveGuiWindowManager(void)
    : QObject(nullptr),
        mp_isPopulated(false),
        mp_isBusy(false),
        mp_mainWindow(nullptr)
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

JveGuiWindowManager::~JveGuiWindowManager(void)
{
}

void
JveGuiWindowManager::populateGui(void)
{
    // main window
    mp_mainWindow = new JveGuiMainWindow;
    mp_mainWindow->show();
    mp_mainWindow->restoreSettings();

    // windowable docks (can be show as dockable windows)
    foreach (
        JveGuiWindowableDock *dock,
        mp_mainWindow->windowableDocks()
    ) {
        dock->setUp();
    }

    // activate main window
    mp_mainWindow->activateWindow();

    // slot show loading project progress dialog
    connect(
        &JveProjectSignals,
        SIGNAL(wantShowLoadingProjectProgress()),
        this,
        SLOT(slotShowLoadingProjectProgressDialog()),
        Qt::QueuedConnection
    );
    // slot modified project warning
    connect(
        &JveProjectSignals,
        SIGNAL(wantShowModifiedProjectWarning(int, QString)),
        this,
        SLOT(slotShowModifiedProjectWarning(int, QString)),
        Qt::QueuedConnection
    );

    // slot open project dialog
    connect(
        &JveProjectSignals,
        SIGNAL(wantShowOpenProjectDialog()),
        this,
        SLOT(slotShowOpenProjectDialog()),
        Qt::QueuedConnection
    );
    // slot save project dialog
    connect(
        &JveProjectSignals,
        SIGNAL(wantShowSaveProjectDialog(int, QString)),
        this,
        SLOT(slotShowSaveProjectDialog(int, QString)),
        Qt::QueuedConnection
    );

    // slot add project sources media items dialog
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(wantShowAddMediaItemsDialog()),
        this,
        SLOT(slotShowAddProjectSourcesMediaItemsDialog()),
        Qt::DirectConnection
    );
    // slot add project sources images sequence item dialog
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(wantShowAddImagesSequenceItemDialog()),
        this,
        SLOT(slotShowAddProjectSourcesImagesSequenceItemDialog()),
        Qt::DirectConnection
    );

    // slot show project sources item properties dialog
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(wantShowItemPropertiesDialog(JveSourcesItemStruct)),
        this,
        SLOT(slotShowProjectSourcesItemPropertiesDialog(JveSourcesItemStruct)),
        Qt::DirectConnection
    );

    // slot preferences dialog
    connect(
        &JveGlobalSignals,
        SIGNAL(wantShowPreferencesDialog()),
        this,
        SLOT(slotShowPreferencesDialog()),
        Qt::DirectConnection
    );

    // slot keyboard shortcuts info
    connect(
        &JveGlobalSignals,
        SIGNAL(wantShowKeyboardShortcutsInfo()),
        this,
        SLOT(slotShowKeyboardShortcutsInfo()),
        Qt::DirectConnection
    );
    // slot about Jve
    connect(
        &JveGlobalSignals,
        SIGNAL(wantShowAboutJveDialog()),
        this,
        SLOT(slotShowAboutJveDialog()),
        Qt::DirectConnection
    );

    // set populated
    mp_isPopulated = true;
}

void
JveGuiWindowManager::depopulateGui(void)
{
    if (mp_isPopulated) {

        // set depopulated
        mp_isPopulated = false;

        // windowable docks
        foreach (
            JveGuiWindowableDock *dock,
            mp_mainWindow->windowableDocks()
        ) {
            dock->upSet();
        }

        // main window
        mp_mainWindow->saveSettings();
        mp_mainWindow->hide();

        delete mp_mainWindow;

    }
}

void
JveGuiWindowManager::slotQuitAccepted(void)
{
    qApp->quit();
}

void
JveGuiWindowManager::slotStateChanged(const int state)
{
    if (state & JveState::Busy) {
        mp_isBusy = true;
        QApplication::setOverrideCursor(Qt::BusyCursor);
    } else if (mp_isBusy) {
        mp_isBusy = false;
        QApplication::restoreOverrideCursor();
    }
}

void
JveGuiWindowManager::slotShowReport(const JveReport &report)
{
    switch (report.type()) {

        case JveReport::Error:
        case JveReport::Warning:
        case JveReport::Info:
            {
                if (mp_isPopulated) {
                    mp_mainWindow->clearStatusBarMessage();
                }

                QPointer<JveGuiReportBox>
                    reportBox = new JveGuiReportBox(qApp->activeWindow());

                reportBox->exec(report);
                delete reportBox;
            }
        break;

        case JveReport::Message:
            {
                if (mp_isPopulated) {
                    mp_mainWindow->showStatusBarMessage(report.message());
                }
            }
        break;

        case JveReport::Success:
            {
                if (report.isForced()) {
                    if (mp_isPopulated) {
                        mp_mainWindow->clearStatusBarMessage();
                    }

                    QPointer<JveGuiReportBox>
                        reportBox = new JveGuiReportBox(qApp->activeWindow());

                    reportBox->exec(report);
                    delete reportBox;

                } else if (mp_isPopulated) {
                    mp_mainWindow->showStatusBarMessage(report.message());
                }
            }
        break;

        default:
        break;

    }
}

void
JveGuiWindowManager::slotShowLoadingProjectProgressDialog(void)
{
    QPointer<JveGuiLoadingProjectProgressDialod>
        dialog = new JveGuiLoadingProjectProgressDialod(qApp->activeWindow());

    if (QDialog::Rejected == dialog->exec()) {
        JveLoadingProjectMutex.lock();
        Jve.setLoadingProjectProcessRejected(true);
        JveLoadingProjectMutex.unlock();
    }

    delete dialog;
}

void
JveGuiWindowManager::slotShowModifiedProjectWarning(
    const int      options,
    const QString &loadingProjectUrl
)
{
    QPointer<JveGuiModifiedProjectWarning>
        warning = new JveGuiModifiedProjectWarning(qApp->activeWindow());

    switch (warning->exec()) {
        case QMessageBox::Save:
            emit JveProjectSignals.wantSaveProject(
                    options,
                    loadingProjectUrl
            );
        break;
        case QMessageBox::Discard:
            emit JveProjectSignals.wantRouteOptions(
                    options | JveOption::CloseProjectForced,
                    loadingProjectUrl,
                    nullptr
            );
        break;
        case QMessageBox::Cancel:
            {
                if (options & JveOption::Quit) {
                    JveGlobalSignals.wantRejectQuit();
                }
            }
        break;
        default:
        break;
    }

    delete warning;
}

void
JveGuiWindowManager::slotShowSaveProjectDialog(
    const int      options,
    const QString &loadingProjectUrl
)
{
    QPointer<JveGuiSaveProjectDialog>
        dialog = new JveGuiSaveProjectDialog(qApp->activeWindow());

    if (QDialog::Accepted == dialog->exec() && nullptr != dialog) {
        emit JveProjectSignals.wantRouteOptions(
                options | JveOption::SaveProject,
                loadingProjectUrl,
                dialog->getNormalizedFilePath()
        );
    }

    delete dialog;
}

void
JveGuiWindowManager::slotShowOpenProjectDialog(void)
{
    QPointer<JveGuiOpenProjectDialog>
        dialog = new JveGuiOpenProjectDialog(qApp->activeWindow());

    if (QDialog::Accepted == dialog->exec() && nullptr != dialog) {
        emit JveProjectSignals
                    .wantLoadProject(dialog->selectedFiles().first());
    }

    delete dialog;
}

void
JveGuiWindowManager::slotShowAddProjectSourcesMediaItemsDialog(void)
{
    QPointer<JveGuiAddProjectSourcesMediaItemsDialog>
        dialog = new JveGuiAddProjectSourcesMediaItemsDialog(
            qApp->activeWindow()
        );

    if (QDialog::Accepted == dialog->exec() && nullptr != dialog) {
        emit JveProjectSourcesSignals
                    .wantAddItems(dialog->selectedFiles());
    }

    delete dialog;
}

void
JveGuiWindowManager::slotShowAddProjectSourcesImagesSequenceItemDialog(void)
{
    QPointer<JveGuiAddProjectSourcesImagesSequenceItemDialog>
        dialog = new JveGuiAddProjectSourcesImagesSequenceItemDialog(
            qApp->activeWindow()
        );

    if (QDialog::Accepted == dialog->exec() && nullptr != dialog) {
        emit JveProjectSourcesSignals
                    .wantAddImagesSequenceItem(dialog->selectedFiles());
    }

    delete dialog;
}

void
JveGuiWindowManager::slotShowProjectSourcesItemPropertiesDialog(
    const JveSourcesItemStruct &itemStruct
)
{
    QPointer<JveGuiProjectSourcesItemPropertiesDialog>
        dialog = new JveGuiProjectSourcesItemPropertiesDialog(
            qApp->activeWindow(),
            itemStruct
        );

    dialog->exec();

    delete dialog;
}

void
JveGuiWindowManager::slotShowPreferencesDialog(void)
{
    QPointer<JveGuiPreferencesDialog>
        dialog = new JveGuiPreferencesDialog(qApp->activeWindow());

    dialog->exec();

    delete dialog;
}

void
JveGuiWindowManager::slotShowKeyboardShortcutsInfo(void)
{
    QPointer<JveGuiKeyboardShortcutsInfo>
        info = new JveGuiKeyboardShortcutsInfo(qApp->activeWindow());

    info->exec();

    delete info;
}

void
JveGuiWindowManager::slotShowAboutJveDialog(void)
{
    QPointer<JveGuiAboutJveBox>
        about = new JveGuiAboutJveBox(qApp->activeWindow());

    about->exec();

    delete about;
}


