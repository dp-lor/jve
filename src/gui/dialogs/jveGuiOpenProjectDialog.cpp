

#include "jveGuiOpenProjectDialog.h"


#include <QEvent>


#include "../../core/definitions/jveProjectFileDefines.h"
#include "../definitions/jveGuiWindowsSettingsDefines.h"

#include "../../core/application/jveSettings.h"


jveGuiOpenProjectDialog::jveGuiOpenProjectDialog(QWidget *parent)
    : QFileDialog(parent)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setOption(QFileDialog::DontUseNativeDialog);
    setOption(QFileDialog::DontUseSheet);
    setAcceptMode(QFileDialog::AcceptOpen);
    setFileMode(QFileDialog::ExistingFile);
    setOption(QFileDialog::ReadOnly);

    // restore state
    jveSettings.lock();

    if (
        jveSettings.contains(
            JVE_GUI_SETTINGS_OPEN_PROJECT_DIALOG_STATE
        )
    ) {
        restoreState(
            jveSettings.value(
                JVE_GUI_SETTINGS_OPEN_PROJECT_DIALOG_STATE
            ).toByteArray()
        );
    }

    jveSettings.unlock();

    // initial translate
    updateTranslations();
}

jveGuiOpenProjectDialog::~jveGuiOpenProjectDialog(void)
{
    jveSettings.lock();

    jveSettings.setValue(
        JVE_GUI_SETTINGS_OPEN_PROJECT_DIALOG_STATE,
        saveState()
    );

    jveSettings.sync();
    jveSettings.unlock();
}

void
jveGuiOpenProjectDialog::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QFileDialog::changeEvent(event);
}

void
jveGuiOpenProjectDialog::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_open_project_dialog_title"));

    // filters
    setNameFilters(
        QStringList()
            << tr("gui_open_project_dialog_filter_jve_project_file")
                .append(
                    " (*." JVE_PROJECT_FILE_EXTENSION ")"
                )
            << tr("gui_open_project_dialog_filter_all_files")
                .append(" (*)")
    );
}


