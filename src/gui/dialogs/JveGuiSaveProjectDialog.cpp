

#include "JveGuiSaveProjectDialog.h"


#include <QEvent>
#include <QFileInfo>


#include "../../core/definitions/JveProjectFileDefines.h"
#include "../definitions/JveGuiWindowsSettingsDefines.h"

#include "../../core/application/JveSettings.h"


JveGuiSaveProjectDialog::JveGuiSaveProjectDialog(QWidget *parent)
    : QFileDialog(parent)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setOption(QFileDialog::DontUseNativeDialog);
    setOption(QFileDialog::DontUseSheet);
    setAcceptMode(QFileDialog::AcceptSave);
    setFileMode(QFileDialog::AnyFile);

    // restore state
    JveSettings.lock();

    if (
        JveSettings.contains(
            JVE_GUI_SETTINGS_SAVE_PROJECT_DIALOG_STATE
        )
    ) {
        restoreState(
            JveSettings.value(
                JVE_GUI_SETTINGS_SAVE_PROJECT_DIALOG_STATE
            ).toByteArray()
        );
    }

    JveSettings.unlock();

    // initial translate
    updateTranslations();
}

JveGuiSaveProjectDialog::~JveGuiSaveProjectDialog(void)
{
    JveSettings.lock();

    JveSettings.setValue(
        JVE_GUI_SETTINGS_SAVE_PROJECT_DIALOG_STATE,
        saveState()
    );

    JveSettings.sync();
    JveSettings.unlock();
}

QString
JveGuiSaveProjectDialog::getNormalizedFilePath(void) const
{
    QFileInfo info(selectedFiles().first());
    info.setCaching(false);

    QString dirPath    = info.absoluteDir().absolutePath();
    QString filePath   = info.absoluteFilePath();
    int     fileExtPos = filePath.lastIndexOf(".");

    // TODO некорректно отрабатывает если я хочу имя файла с точками
    return (
        (
            fileExtPos == (dirPath.length() + 1)
                ? filePath
                : filePath.left(fileExtPos)
        )
            .append(".")
            .append(JVE_PROJECT_FILE_EXTENSION)
    );
}

void
JveGuiSaveProjectDialog::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QFileDialog::changeEvent(event);
}

void
JveGuiSaveProjectDialog::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_save_project_dialog_title"));

    // filters
    setNameFilters(
        QStringList()
            << tr("gui_save_project_dialog_filter_jve_project_file")
                .append(
                    " (*." JVE_PROJECT_FILE_EXTENSION ")"
                )
    );
}


