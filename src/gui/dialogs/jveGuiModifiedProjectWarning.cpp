

#include "jveGuiModifiedProjectWarning.h"


#include <QEvent>


#include "../../core/definitions/jveDefines.h"


jveGuiModifiedProjectWarning::jveGuiModifiedProjectWarning(QWidget *parent)
    : QMessageBox(parent)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setIcon(QMessageBox::Warning);
    setWindowTitle(JVE_NAME_STRING);

    // buttons
    setStandardButtons(
        QMessageBox::Save
            | QMessageBox::Discard
            | QMessageBox::Cancel
    );
    setDefaultButton(QMessageBox::Save);

    // initial translate
    updateTranslations();
}

jveGuiModifiedProjectWarning::~jveGuiModifiedProjectWarning(void)
{
}

void
jveGuiModifiedProjectWarning::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMessageBox::changeEvent(event);
}

void
jveGuiModifiedProjectWarning::updateTranslations(void)
{
    // warning text
    setText(tr("gui_modified_project_warning_text"));

    // informative text
    setInformativeText(
        tr("gui_modified_project_warning_informative_text")
    );
}


