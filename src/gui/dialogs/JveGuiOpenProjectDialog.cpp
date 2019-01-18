

#include "JveGuiOpenProjectDialog.h"


#include <QEvent>


#include "../../core/definitions/JveProjectFileDefines.h"
#include "../definitions/JveGuiWindowsSettingsDefines.h"

#include "../../core/application/JveSettings.h"


JveGuiOpenProjectDialog::JveGuiOpenProjectDialog(QWidget *parent)
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
    JveSettings.lock();

    if (
        JveSettings.contains(
            JVE_GUI_SETTINGS_OPEN_PROJECT_DIALOG_STATE
        )
    ) {
        restoreState(
            JveSettings.value(
                JVE_GUI_SETTINGS_OPEN_PROJECT_DIALOG_STATE
            ).toByteArray()
        );
    }

    JveSettings.unlock();

    // initial translate
    updateTranslations();
}

JveGuiOpenProjectDialog::~JveGuiOpenProjectDialog(void)
{
    JveSettings.lock();

    JveSettings.setValue(
        JVE_GUI_SETTINGS_OPEN_PROJECT_DIALOG_STATE,
        saveState()
    );

    JveSettings.sync();
    JveSettings.unlock();
}

void
JveGuiOpenProjectDialog::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QFileDialog::changeEvent(event);
}

void
JveGuiOpenProjectDialog::updateTranslations(void)
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


