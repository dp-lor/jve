

#include "JveGuiAddProjectSourcesImagesSequenceItemDialog.h"


#include <QEvent>


#include "../../core/definitions/JveProjectSourcesFileExtensionsDefines.h"

#include "../definitions/JveGuiWindowsSettingsDefines.h"
#include "../../core/application/JveSettings.h"


JveGuiAddProjectSourcesImagesSequenceItemDialog
    ::JveGuiAddProjectSourcesImagesSequenceItemDialog(
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
            JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_IMAGES_SEQUENCE_ITEM_DIALOG_STATE
        )
    ) {
        restoreState(
            JveSettings.value(
                JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_IMAGES_SEQUENCE_ITEM_DIALOG_STATE
            ).toByteArray()
        );
    }

    JveSettings.unlock();

    // initial translate
    updateTranslations();
}

JveGuiAddProjectSourcesImagesSequenceItemDialog
    ::~JveGuiAddProjectSourcesImagesSequenceItemDialog(void)
{
    JveSettings.lock();

    JveSettings.setValue(
        JVE_GUI_SETTINGS_ADD_PROJECT_SOURCES_IMAGES_SEQUENCE_ITEM_DIALOG_STATE,
        saveState()
    );

    JveSettings.sync();
    JveSettings.unlock();
}

void
JveGuiAddProjectSourcesImagesSequenceItemDialog::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QFileDialog::changeEvent(event);
}

void
JveGuiAddProjectSourcesImagesSequenceItemDialog::updateTranslations(void)
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
                        JVE_SOURCES_IMAGE_FILE_EXTENSIONS_LIST
                    ")"
                )
            << tr("gui_add_project_sources_images_sequence_item_dialog_filter_all_files")
                .append(" (*)")
    );
}


