

#include "jveGuiWindowManager.h"


#include <QList>
#include <QApplication>
#include <QPointer>
#include <QStringList>


#include "../../core/definitions/jveOption.h"
#include "../../core/definitions/jveState.h"

#include "../../core/signals/jveGlobalSignals.h"
#include "../../core/signals/jveProjectSignals.h"
#include "../../core/signals/jveProjectSourcesSignals.h"

#include "../dialogs/jveGuiReportBox.h"
#include "../dialogs/jveGuiOpenProjectDialog.h"
#include "../dialogs/jveGuiSaveProjectDialog.h"
#include "../dialogs/jveGuiModifiedProjectWarning.h"
#include "../dialogs/jveGuiAddProjectSourcesMediaItemsDialog.h"
#include "../dialogs/jveGuiAddProjectSourcesImagesSequenceItemDialog.h"
#include "../dialogs/jveGuiProjectSourcesItemPropertiesDialog.h"
#include "../dialogs/jveGuiPreferencesDialog.h"
#include "../dialogs/jveGuiKeyboardShortcutsInfo.h"
#include "../dialogs/jveGuiAboutJveBox.h"

#include "jveGuiMainWindow.h"
#include "../docks/jveGuiWindowableDock.h"


jveGuiWindowManager::jveGuiWindowManager(void)
    : QObject(Q_NULLPTR),
        mp_isPopulated(false),
        mp_isBusy(false),
        mp_mainWindow(Q_NULLPTR)
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

jveGuiWindowManager::~jveGuiWindowManager(void)
{
}

void
jveGuiWindowManager::populateGui(void)
{
    // main window
    mp_mainWindow = new jveGuiMainWindow;
    mp_mainWindow->restoreSettings();
    mp_mainWindow->show();

    // windowable docks (can be show as dockable windows)
    QList<jveGuiWindowableDock *> wds = mp_mainWindow->windowableDocks();
    for (int i = 0; i < wds.size(); i += 1) {
        wds.at(i)->initialShow();
    }

    // activate main window
    mp_mainWindow->activateWindow();

    // slot modified project warning
    connect(
        &jveProjectSignals,
        SIGNAL(wantShowModifiedProjectWarning(int, QString)),
        this,
        SLOT(slotShowModifiedProjectWarning(int, QString)),
        Qt::QueuedConnection
    );

    // slot open project dialog
    connect(
        &jveProjectSignals,
        SIGNAL(wantShowOpenProjectDialog()),
        this,
        SLOT(slotShowOpenProjectDialog()),
        Qt::QueuedConnection
    );
    // slot save project dialog
    connect(
        &jveProjectSignals,
        SIGNAL(wantShowSaveProjectDialog(int, QString)),
        this,
        SLOT(slotShowSaveProjectDialog(int, QString)),
        Qt::QueuedConnection
    );

    // slot add project sources media items dialog
    connect(
        &jveProjectSourcesSignals,
        SIGNAL(wantShowAddMediaItemsDialog()),
        this,
        SLOT(slotShowAddProjectSourcesMediaItemsDialog()),
        Qt::DirectConnection
    );
    // slot add project sources images sequence item dialog
    connect(
        &jveProjectSourcesSignals,
        SIGNAL(wantShowAddImagesSequenceItemDialog()),
        this,
        SLOT(slotShowAddProjectSourcesImagesSequenceItemDialog()),
        Qt::DirectConnection
    );

    // slot show project sources item properties dialog
    connect(
        &jveProjectSourcesSignals,
        SIGNAL(wantShowItemPropertiesDialog(jveSourcesItemStruct)),
        this,
        SLOT(slotShowProjectSourcesItemPropertiesDialog(jveSourcesItemStruct)),
        Qt::DirectConnection
    );

    // slot preferences dialog
    connect(
        &jveGlobalSignals,
        SIGNAL(wantShowPreferencesDialog()),
        this,
        SLOT(slotShowPreferencesDialog()),
        Qt::DirectConnection
    );

    // slot keyboard shortcuts info
    connect(
        &jveGlobalSignals,
        SIGNAL(wantShowKeyboardShortcutsInfo()),
        this,
        SLOT(slotShowKeyboardShortcutsInfo()),
        Qt::DirectConnection
    );
    // slot about jve
    connect(
        &jveGlobalSignals,
        SIGNAL(wantShowAboutJveDialog()),
        this,
        SLOT(slotShowAboutJveDialog()),
        Qt::DirectConnection
    );

    // set populated
    mp_isPopulated = true;
}

void
jveGuiWindowManager::depopulateGui(void)
{
    if (mp_isPopulated) {

        // set depopulated
        mp_isPopulated = false;

        // windowable docks
        QList<jveGuiWindowableDock *> wds = mp_mainWindow->windowableDocks();
        for (int i = 0; i < wds.size(); i += 1) {
            wds.at(i)->finalClose();
        }

        // main window
        mp_mainWindow->saveSettings();
        mp_mainWindow->hide();

        delete mp_mainWindow;

    }
}

void
jveGuiWindowManager::slotQuitAccepted(void)
{
    qApp->quit();
}

void
jveGuiWindowManager::slotStateChanged(const int state)
{
    if (state & jveState::Busy) {
        mp_isBusy = true;
        QApplication::setOverrideCursor(Qt::BusyCursor);
    } else if (mp_isBusy) {
        mp_isBusy = false;
        QApplication::restoreOverrideCursor();
    }
}

void
jveGuiWindowManager::slotShowReport(const jveReport &report)
{
    switch (report.type()) {

        case jveReport::Error:
        case jveReport::Warning:
        case jveReport::Info:
            {
                if (mp_isPopulated) {
                    mp_mainWindow->clearStatusBarMessage();
                }

                QPointer<jveGuiReportBox>
                    reportBox = new jveGuiReportBox(qApp->activeWindow());

                reportBox->exec(report);
                delete reportBox;
            }
        break;

        case jveReport::Message:
            {
                if (mp_isPopulated) {
                    mp_mainWindow->showStatusBarMessage(report.message());
                }
            }
        break;

        case jveReport::Success:
            {
                if (report.isForced()) {
                    if (mp_isPopulated) {
                        mp_mainWindow->clearStatusBarMessage();
                    }

                    QPointer<jveGuiReportBox>
                        reportBox = new jveGuiReportBox(qApp->activeWindow());

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
jveGuiWindowManager::slotShowModifiedProjectWarning(
    const int      options,
    const QString &loadingProjectUrl
)
{
    QPointer<jveGuiModifiedProjectWarning>
        warning = new jveGuiModifiedProjectWarning(qApp->activeWindow());

    switch (warning->exec()) {
        case QMessageBox::Save:
            emit jveProjectSignals.wantSaveProject(
                    options,
                    loadingProjectUrl
            );
        break;
        case QMessageBox::Discard:
            emit jveProjectSignals.wantRouteOptions(
                    options | jveOption::CloseProjectForced,
                    loadingProjectUrl,
                    Q_NULLPTR
            );
        break;
        case QMessageBox::Cancel:
            {
                if (options & jveOption::Quit) {
                    jveGlobalSignals.wantRejectQuit();
                }
            }
        break;
        default:
        break;
    }

    delete warning;
}

void
jveGuiWindowManager::slotShowSaveProjectDialog(
    const int      options,
    const QString &loadingProjectUrl
)
{
    QPointer<jveGuiSaveProjectDialog>
        dialog = new jveGuiSaveProjectDialog(qApp->activeWindow());

    if (QDialog::Accepted == dialog->exec() && Q_NULLPTR != dialog) {
        emit jveProjectSignals.wantRouteOptions(
                options | jveOption::SaveProject,
                loadingProjectUrl,
                dialog->getNormalizedFilePath()
        );
    }

    delete dialog;
}

void
jveGuiWindowManager::slotShowOpenProjectDialog(void)
{
    QPointer<jveGuiOpenProjectDialog>
        dialog = new jveGuiOpenProjectDialog(qApp->activeWindow());

    if (QDialog::Accepted == dialog->exec() && Q_NULLPTR != dialog) {
        emit jveProjectSignals
                    .wantLoadProject(dialog->selectedFiles().first());
    }

    delete dialog;
}

void
jveGuiWindowManager::slotShowAddProjectSourcesMediaItemsDialog(void)
{
    QPointer<jveGuiAddProjectSourcesMediaItemsDialog>
        dialog = new jveGuiAddProjectSourcesMediaItemsDialog(
            qApp->activeWindow()
        );

    if (QDialog::Accepted == dialog->exec() && Q_NULLPTR != dialog) {
        emit jveProjectSourcesSignals
                    .wantAddItems(dialog->selectedFiles());
    }

    delete dialog;
}

void
jveGuiWindowManager::slotShowAddProjectSourcesImagesSequenceItemDialog(void)
{
    QPointer<jveGuiAddProjectSourcesImagesSequenceItemDialog>
        dialog = new jveGuiAddProjectSourcesImagesSequenceItemDialog(
            qApp->activeWindow()
        );

    if (QDialog::Accepted == dialog->exec() && Q_NULLPTR != dialog) {
        emit jveProjectSourcesSignals
                    .wantAddImagesSequenceItem(dialog->selectedFiles());
    }

    delete dialog;
}

void
jveGuiWindowManager::slotShowProjectSourcesItemPropertiesDialog(
    const jveSourcesItemStruct &itemStruct
)
{
    QPointer<jveGuiProjectSourcesItemPropertiesDialog>
        dialog = new jveGuiProjectSourcesItemPropertiesDialog(
            qApp->activeWindow(),
            itemStruct
        );

    dialog->exec();

    delete dialog;
}

void
jveGuiWindowManager::slotShowPreferencesDialog(void)
{
    QPointer<jveGuiPreferencesDialog>
        dialog = new jveGuiPreferencesDialog(qApp->activeWindow());

    dialog->exec();

    delete dialog;
}

void
jveGuiWindowManager::slotShowKeyboardShortcutsInfo(void)
{
    QPointer<jveGuiKeyboardShortcutsInfo>
        info = new jveGuiKeyboardShortcutsInfo(qApp->activeWindow());

    info->exec();

    delete info;
}

void
jveGuiWindowManager::slotShowAboutJveDialog(void)
{
    QPointer<jveGuiAboutJveBox>
        about = new jveGuiAboutJveBox(qApp->activeWindow());

    about->exec();

    delete about;
}


