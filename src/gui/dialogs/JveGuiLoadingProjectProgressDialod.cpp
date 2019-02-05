

#include "JveGuiLoadingProjectProgressDialod.h"


#include <QEvent>


#include "../../core/definitions/JveDefines.h"
#include "../definitions/JveGuiAppearanceDefines.h"
#include "../definitions/JveGuiWindowsAppearanceDefines.h"

#include "../../core/signals/JveProjectSignals.h"


JveGuiLoadingProjectProgressDialod
    ::JveGuiLoadingProjectProgressDialod(QWidget *parent)
        : QDialog(parent),
            mp_layout(this),
            mp_title(this),
            mp_progress(this),
            mp_description(this),
            mp_buttonsWrapper(this),
            mp_buttonsLayout(&mp_buttonsWrapper),
            mp_cancelButton(&mp_buttonsWrapper)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setMinimumWidth(JVE_GUI_DIALOG_MIN_WIDTH);
    // window title
    setWindowTitle(JVE_NAME_STRING);

    // layout
    mp_layout.setMargin(JVE_GUI_BIG_MARGIN_SIZE);
    mp_layout.setSpacing(JVE_GUI_BIG_VERTICAL_SPACE);
    mp_layout.setAlignment(Qt::AlignVCenter);

    // title label
    mp_layout.addWidget(&mp_title);

    // progress bar
    mp_progress.setRange(0, 100);
    mp_progress.setValue(0);
    mp_progress.setFormat("%p%");
    mp_progress.setTextVisible(true);
    mp_layout.addWidget(&mp_progress);

    // description label
    mp_layout.addWidget(&mp_description);

    // buttons wrapper
    mp_layout.addWidget(&mp_buttonsWrapper);

    // buttons wrapper layout
    mp_buttonsLayout.setMargin(0);
    mp_buttonsLayout.setSpacing(0);
    mp_buttonsLayout.setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    // cancel button
    mp_buttonsLayout.addWidget(&mp_cancelButton);

    // slot reject
    connect(
        &mp_cancelButton,
        SIGNAL(clicked()),
        this,
        SLOT(reject()),
        Qt::DirectConnection
    );

    // slot progress updated
    connect(
        &JveProjectSignals,
        SIGNAL(loadingProgressUpdated(int)),
        this,
        SLOT(slotProgressUpdated(int)),
        Qt::QueuedConnection
    );
    /*// slot process completed
    connect(
        &JveProjectSignals,
        SIGNAL(loadingProcessCompleted()),
        this,
        SLOT(slotProcessCompleted()),
        Qt::QueuedConnection
    );*/

    // initial translate
    updateTranslations();
}

JveGuiLoadingProjectProgressDialod::~JveGuiLoadingProjectProgressDialod(void)
{
}

void
JveGuiLoadingProjectProgressDialod::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QDialog::changeEvent(event);
}

void
JveGuiLoadingProjectProgressDialod::slotProgressUpdated(const int value)
{
    mp_progress.setValue(value);
}

void
JveGuiLoadingProjectProgressDialod::updateTranslations(void)
{
    // title label
    mp_title.setText(
        tr("gui_loading_project_progress_dialog_title_label")
    );

    // cancel button
    mp_cancelButton.setText(
        tr("gui_loading_project_progress_dialog_cancel_button")
    );
}


