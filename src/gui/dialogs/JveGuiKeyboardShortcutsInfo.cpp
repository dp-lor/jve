

#include "JveGuiKeyboardShortcutsInfo.h"


#include <QEvent>


JveGuiKeyboardShortcutsInfo::JveGuiKeyboardShortcutsInfo(QWidget *parent)
    : QDialog(parent),
        mp_layout(this),
        mp_label(this),
        mp_table(this)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setMinimumSize(400, 400);

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);
    mp_layout.setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    // label
    mp_label.setFixedHeight(5);
    mp_layout.addWidget(&mp_label);

    // table
    mp_table.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mp_table.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    mp_table.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mp_layout.addWidget(&mp_table);

    // initial translate
    updateTranslations();
}

JveGuiKeyboardShortcutsInfo::~JveGuiKeyboardShortcutsInfo(void)
{
}

void
JveGuiKeyboardShortcutsInfo::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QDialog::changeEvent(event);
}

void
JveGuiKeyboardShortcutsInfo::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_keyboard_shortcuts_info_title"));
}


