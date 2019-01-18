

#include "JveGuiAddProjectSourcesMediaItemsDialog.h"


#include <QEvent>


#include "../../core/definitions/JveProjectSourcesFileExtensionsDefines.h"

#include "../definitions/JveGuiWindowsSettingsDefines.h"
#include "../../core/application/JveSettings.h"


JveGuiAddProjectSourcesMediaItemsDialog
    ::JveGuiAddProjectSourcesMediaItemsDialog(
        QWidget *parent
    ) : QFileDialog(parent)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setOption(QFileDialog::DontUseNativeDialog);
    setOption(QFileDialog::DontUseSheet);
    setAcceptMode(QFileDialog::AcceptOpen);
    setFileMode(QFileDialog::ExistingFiles);
    setOption(QFileDialog::ReadOnly);

    // restore state
    JveSettings.lock();

    if (
        JveSettings.contains(
            JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_MEDIA_ITEMS_DIALOG_STATE
        )
    ) {
        restoreState(
            JveSettings.value(
                JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_MEDIA_ITEMS_DIALOG_STATE
            ).toByteArray()
        );
    }

    JveSettings.unlock();

    // initial translate
    updateTranslations();
}

JveGuiAddProjectSourcesMediaItemsDialog
    ::~JveGuiAddProjectSourcesMediaItemsDialog(void)
{
    JveSettings.lock();

    JveSettings.setValue(
        JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_MEDIA_ITEMS_DIALOG_STATE,
        saveState()
    );

    JveSettings.sync();
    JveSettings.unlock();
}

void
JveGuiAddProjectSourcesMediaItemsDialog::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QFileDialog::changeEvent(event);
}

void
JveGuiAddProjectSourcesMediaItemsDialog::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_add_project_sources_media_items_dialog_title"));

    // filters
    setNameFilters(

        QStringList()
            << tr("gui_add_project_sources_media_items_dialog_filter_all_formats")
                .append(
                    " "
                    "("
                        JVE_SOURCES_VIDEO_FILE_EXTENSIONS_LIST
                        " "
                        JVE_SOURCES_IMAGE_FILE_EXTENSIONS_LIST
                        " "
                        JVE_SOURCES_AUDIO_FILE_EXTENSIONS_LIST
                        " "
                        JVE_SOURCES_TEXT_FILE_EXTENSIONS_LIST
                    ")"
                )
            << tr("gui_add_project_sources_media_items_dialog_filter_video")
                .append(
                    " "
                    "("
                        JVE_SOURCES_VIDEO_FILE_EXTENSIONS_LIST
                    ")"
                )
            << tr("gui_add_project_sources_media_items_dialog_filter_images")
                .append(
                    " "
                    "("
                        JVE_SOURCES_IMAGE_FILE_EXTENSIONS_LIST
                    ")"
                )
            << tr("gui_add_project_sources_media_items_dialog_filter_audio")
                .append(
                    " "
                    "("
                        JVE_SOURCES_AUDIO_FILE_EXTENSIONS_LIST
                    ")"
                )
            << tr("gui_add_project_sources_media_items_dialog_filter_texts")
                .append(
                    " "
                    "("
                        JVE_SOURCES_TEXT_FILE_EXTENSIONS_LIST
                    ")"
                )
            << tr("gui_add_project_sources_media_items_dialog_filter_all_files")
                .append(" (*)")
    );
}


