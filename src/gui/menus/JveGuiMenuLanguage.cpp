

#include "JveGuiMenuLanguage.h"


#include <QLocale>


#include "../../core/definitions/JveLocalizationDefines.h"
#include "../../core/signals/JveGlobalSignals.h"


JveGuiMenuLanguage::JveGuiMenuLanguage(QWidget *parent)
    : QMenu(parent),
        localeActionsGroup(this),
        actionEnUs(this),
        actionRuRu(this),
        actionReset(this)
{
    // menu action
    menuAction()->setText(QString("&Language").toUtf8());

    // locale actions group
    localeActionsGroup.setExclusive(true);
    connect(
        &localeActionsGroup,
        SIGNAL(triggered(QAction *)),
        this,
        SLOT(slotCatchSetLocale(QAction *)),
        Qt::DirectConnection
    );

    // locale actions
    setUpLocaleAction(&actionEnUs, JVE_LOCALIZATION_LOCALE_EN_US);
    setUpLocaleAction(&actionRuRu, JVE_LOCALIZATION_LOCALE_RU_RU);

    // separator
    addSeparator();

    // reset
    addAction(&actionReset);
    connect(
        &actionReset,
        SIGNAL(triggered()),
        &JveGlobalSignals,
        SIGNAL(wantSetSystemLocale()),
        Qt::DirectConnection
    );

    // initial translate
    updateTranslations();

    // slot locale changed
    connect(
        &JveGlobalSignals,
        SIGNAL(localeChanged(QString)),
        this,
        SLOT(slotLocaleChanged(QString)),
        Qt::QueuedConnection
    );
}

JveGuiMenuLanguage::~JveGuiMenuLanguage(void)
{
}

void
JveGuiMenuLanguage::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
JveGuiMenuLanguage::setUpLocaleAction(
          QAction *action,
    const QString &locale
)
{
    action->setCheckable(true);
    action->setData(locale);
    action->setText(QLocale::languageToString(QLocale(locale).language()));

    addAction(action);
    localeActionsGroup.addAction(action);
}

void
JveGuiMenuLanguage::updateLocaleActionState(
          QAction *action,
    const QString &locale
)
{
    action->setChecked(action->data().toString() == locale);
}

void
JveGuiMenuLanguage::updateTranslations(void)
{
    // reset
    actionReset.setText(tr("gui_menu_language_action_reset_text"));
    actionReset.setStatusTip(
        tr("gui_menu_language_action_reset_status_tip")
    );
}

void
JveGuiMenuLanguage::slotLocaleChanged(const QString &locale)
{
    updateLocaleActionState(&actionEnUs, locale);
    updateLocaleActionState(&actionRuRu, locale);
}

void
JveGuiMenuLanguage::slotCatchSetLocale(QAction *action)
{
    if (nullptr != action) {
        emit JveGlobalSignals.wantSetLocale(action->data().toString());
    }
}


