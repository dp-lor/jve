

#include "JveGuiProjectSourcesItemPropertiesDialog.h"


#include <QEvent>
#include <QDebug>


#include "../../core/signals/JveProjectSourcesSignals.h"


JveGuiProjectSourcesItemPropertiesDialog
    ::JveGuiProjectSourcesItemPropertiesDialog(
              QWidget              *parent,
        const JveSourcesItemStruct &item
) : QDialog(parent),
        mp_item(item),
        mp_layout(this),
        mp_buttonsBox(this),
        mp_buttonsBoxLayout(&mp_buttonsBox),
        mp_btnSave(&mp_buttonsBox),
        mp_btnClose(&mp_buttonsBox)
{
    // properties
    setWindowModality(Qt::ApplicationModal);

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);

    // buttons box
    mp_buttonsBox.setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Minimum
    );
    mp_layout.addWidget(&mp_buttonsBox);

    // buttons box layout
    mp_buttonsBoxLayout.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // save button
    mp_buttonsBoxLayout.addWidget(&mp_btnSave);

    // close button
    mp_buttonsBoxLayout.addWidget(&mp_btnClose);
    connect(
        &mp_btnClose,
        SIGNAL(released()),
        this,
        SLOT(reject()),
        Qt::DirectConnection
    );

    //mp_btnSave.hide();

    /*qDebug() << itemStruct.id;
    qDebug() << itemStruct.type;
    qDebug() << itemStruct.name;
    qDebug() << itemStruct.fileName;
    qDebug() << itemStruct.filePath;*/

    // layout
    /*mp_layout = new QVBoxLayout(this);
    mp_layout->setContentsMargins(10, 10, 10, 10);
    // main tabs widget
    mp_mainTabs = new QTabWidget(this);
    mp_layout->addWidget(mp_mainTabs);

    // add tabs
    mp_mainTabs->addTab(new QWidget, QObject::tr("General"));
    mp_mainTabs->addTab(new QWidget, QObject::tr("Resources"));
    mp_mainTabs->addTab(new QWidget, QObject::tr("Appearance"));
    mp_mainTabs->addTab(new QWidget, QObject::tr("Other"));*/

    // initial translate
    updateTranslations();


    //emit JveProjectSourcesSignals.wantModifyItem(mp_item);
}

JveGuiProjectSourcesItemPropertiesDialog
    ::~JveGuiProjectSourcesItemPropertiesDialog(void)
{
}

void
JveGuiProjectSourcesItemPropertiesDialog::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QDialog::changeEvent(event);
}

void
JveGuiProjectSourcesItemPropertiesDialog::updateTranslations(void)
{
    // title
    setWindowTitle(
        tr("gui_project_sources_item_properties_dialog_title")
    );

    // close button
    mp_btnClose.setText(
        tr("gui_project_sources_item_properties_dialog_close_button_text")
    );

    // save button
    mp_btnSave.setText(
        tr("gui_project_sources_item_properties_dialog_save_button_text")
    );
}


