

#include "jveGuiSaveProjectDialog.h"


#include <QEvent>
#include <QFileInfo>


#include "../../core/definitions/jveProjectFileDefines.h"
#include "../definitions/jveGuiWindowsSettingsDefines.h"

#include "../../core/application/jveSettings.h"


jveGuiSaveProjectDialog::jveGuiSaveProjectDialog(QWidget *parent)
    : QFileDialog(parent)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setOption(QFileDialog::DontUseNativeDialog);
    setOption(QFileDialog::DontUseSheet);
    setAcceptMode(QFileDialog::AcceptSave);
    setFileMode(QFileDialog::AnyFile);

    // restore state
    jveSettings.lock();

    if (
        jveSettings.contains(
            JVE_GUI_SETTINGS_SAVE_PROJECT_DIALOG_STATE
        )
    ) {
        restoreState(
            jveSettings.value(
                JVE_GUI_SETTINGS_SAVE_PROJECT_DIALOG_STATE
            ).toByteArray()
        );
    }

    jveSettings.unlock();

    // initial translate
    updateTranslations();
}

jveGuiSaveProjectDialog::~jveGuiSaveProjectDialog(void)
{
    jveSettings.lock();

    jveSettings.setValue(
        JVE_GUI_SETTINGS_SAVE_PROJECT_DIALOG_STATE,
        saveState()
    );

    jveSettings.sync();
    jveSettings.unlock();
}

QString
jveGuiSaveProjectDialog::getNormalizedFilePath(void) const
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
jveGuiSaveProjectDialog::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QFileDialog::changeEvent(event);
}

void
jveGuiSaveProjectDialog::updateTranslations(void)
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


