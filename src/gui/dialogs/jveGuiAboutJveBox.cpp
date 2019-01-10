

#include "jveGuiAboutJveBox.h"


#include <QEvent>


#include "../../core/definitions/jveDefines.h"
#include "../definitions/jveGuiMediaDefines.h"


jveGuiAboutJveBox::jveGuiAboutJveBox(QWidget *parent)
    : QMessageBox(parent)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setIconPixmap(QPixmap(JVE_GUI_ICON_JVE));

    // ok button
    setStandardButtons(QMessageBox::Ok);
    setDefaultButton(QMessageBox::Ok);

    // initial translate
    updateTranslations();
}

jveGuiAboutJveBox::~jveGuiAboutJveBox(void)
{
}

void
jveGuiAboutJveBox::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMessageBox::changeEvent(event);
}

void
jveGuiAboutJveBox::updateTranslations(void)
{
    // title
    setWindowTitle(
        tr("gui_about_jve_box_title%1")
            .arg(JVE_NAME_STRING)
    );

    // text
    setText(
        tr("gui_about_jve_box_text%1")
            .arg(JVE_VERSION_STRING)
            .toHtmlEscaped()
    );
}


