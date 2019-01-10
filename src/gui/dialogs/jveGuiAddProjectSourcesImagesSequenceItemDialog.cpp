

#include "jveGuiAddProjectSourcesImagesSequenceItemDialog.h"


#include <QEvent>


#include "../../core/definitions/jveProjectFileDefines.h"
#include "../../core/definitions/jveProjectSourcesItemFileDefines.h"

#include "../definitions/jveGuiWindowsSettingsDefines.h"
#include "../../core/application/jveSettings.h"


jveGuiAddProjectSourcesImagesSequenceItemDialog
    ::jveGuiAddProjectSourcesImagesSequenceItemDialog(
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
    jveSettings.lock();

    if (
        jveSettings.contains(
            JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_IMAGES_SEQUENCE_ITEM_DIALOG_STATE
        )
    ) {
        restoreState(
            jveSettings.value(
                JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_IMAGES_SEQUENCE_ITEM_DIALOG_STATE
            ).toByteArray()
        );
    }

    jveSettings.unlock();

    // initial translate
    updateTranslations();
}

jveGuiAddProjectSourcesImagesSequenceItemDialog
    ::~jveGuiAddProjectSourcesImagesSequenceItemDialog(void)
{
    jveSettings.lock();

    jveSettings.setValue(
        JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_IMAGES_SEQUENCE_ITEM_DIALOG_STATE,
        saveState()
    );

    jveSettings.sync();
    jveSettings.unlock();
}

void
jveGuiAddProjectSourcesImagesSequenceItemDialog::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QFileDialog::changeEvent(event);
}

void
jveGuiAddProjectSourcesImagesSequenceItemDialog::updateTranslations(void)
{
    // title
    setWindowTitle(
        tr("gui_add_project_sources_images_sequence_item_dialog_title")
    );

    // filters
    setNameFilters(
        QStringList()
            << tr("gui_add_project_sources_images_sequence_item_dialog_filter_images")
                .append(
                    " "
                    "("
                        JVE_PROJECT_SOURCES_ITEM_IMAGE_FILE_EXTENSIONS_LIST
                    ")"
                )
            << tr("gui_add_project_sources_images_sequence_item_dialog_filter_all_files")
                .append(" (*)")
    );
}


