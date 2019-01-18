

#include "JveLocalizationPrivate.h"


#include <QLocale>
#include <QLibraryInfo>
#include <QCoreApplication>


#include "../definitions/JveLocalizationDefines.h"
#include "../definitions/JveLocalizationMode.h"

#include "../mutexes/JveLocalizationMutex.h"
#include "../application/JveSettings.h"
#include "../signals/JveGlobalSignals.h"

#include "JveTr.h"


JveLocalizationPrivate JveLocalization;


JveLocalizationPrivate::JveLocalizationPrivate(void)
    : QObject(nullptr),
        mp_mode(JveLocalizationMode::None),
        mp_locale(JVE_LOCALIZATION_FALLBACK_LOCALE),
        mp_qtTranslator(this),
        mp_coreTranslator(this),
        mp_guiTranslator(this)
{
}

JveLocalizationPrivate::~JveLocalizationPrivate(void)
{
}

void
JveLocalizationPrivate::initForCli(void)
{
    mp_mode |= JveLocalizationMode::Cli;

    setSystemLocale();
}

void
JveLocalizationPrivate::initForGui(void)
{
    mp_mode |= JveLocalizationMode::Gui;

    setLocaleFromSettings();
    wakeUp();
}

void
JveLocalizationPrivate::emitLocaleChangedSignal(void)
{
    emit JveGlobalSignals.localeChanged(mp_locale);
}

void
JveLocalizationPrivate::saveSettings(void)
{
    JveSettings.lock();

    JveLocalizationMutex.lock();

    JveSettings.setValue(
        JVE_SETTINGS_LOCALIZATION_LOCALE,
        mp_locale
    );

    JveLocalizationMutex.unlock();

    JveSettings.sync();
    JveSettings.unlock();
}

void
JveLocalizationPrivate::setSystemLocale(void)
{
    loadTranslationsByLocale(QLocale::system().name());
}

void
JveLocalizationPrivate::setLocaleFromSettings(void)
{
    JveSettings.lock();

    QString locale = JveSettings.contains(JVE_SETTINGS_LOCALIZATION_LOCALE)
        ? JveSettings.value(JVE_SETTINGS_LOCALIZATION_LOCALE).toString()
        : QLocale::system().name();

    loadTranslationsByLocale(locale);

    JveSettings.unlock();
}

void
JveLocalizationPrivate::wakeUp(void)
{
    // slot set system locale
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSetSystemLocale()),
        this,
        SLOT(slotSetSystemLocale()),
        Qt::QueuedConnection
    );
    // slot set locale
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSetLocale(QString)),
        this,
        SLOT(slotSetLocale(QString)),
        Qt::QueuedConnection
    );
}

void
JveLocalizationPrivate::loadTranslationsByLocale(const QString &locale)
{
    JveLocalizationMutex.lock();

    // qt translator
    qApp->removeTranslator(&mp_qtTranslator);
    mp_qtTranslator.load(
        JVE_LOCALIZATION_QT_TRANSLATIONS_PREFIX + locale,
        QLibraryInfo::location(QLibraryInfo::TranslationsPath)
    );
    qApp->installTranslator(&mp_qtTranslator);

    // core translator
    qApp->removeTranslator(&mp_coreTranslator);
    if (
        !mp_coreTranslator.load(
            QString(JVE_LOCALIZATION_CORE_TRANSLATIONS_PREFIX)
                + locale
                + JVE_LOCALIZATION_TRANSLATIONS_SUFFIX
        )
    ) {
        mp_coreTranslator.load(
            QString(JVE_LOCALIZATION_CORE_TRANSLATIONS_PREFIX)
                + JVE_LOCALIZATION_FALLBACK_LOCALE
                + JVE_LOCALIZATION_TRANSLATIONS_SUFFIX
        );
    }
    qApp->installTranslator(&mp_coreTranslator);

    // gui translator
    if (mp_mode & JveLocalizationMode::Gui) {
        qApp->removeTranslator(&mp_guiTranslator);
        if (
            !mp_guiTranslator.load(
                QString(JVE_LOCALIZATION_GUI_TRANSLATIONS_PREFIX)
                    + locale
                    + JVE_LOCALIZATION_TRANSLATIONS_SUFFIX
            )
        ) {
            mp_guiTranslator.load(
                QString(JVE_LOCALIZATION_GUI_TRANSLATIONS_PREFIX)
                    + JVE_LOCALIZATION_FALLBACK_LOCALE
                    + JVE_LOCALIZATION_TRANSLATIONS_SUFFIX
            );
        }
        qApp->installTranslator(&mp_guiTranslator);
    }

    // store current locale
    mp_locale = locale;
    // update core translations
    JveTr.update();

    emitLocaleChangedSignal();

    JveLocalizationMutex.unlock();
}

void
JveLocalizationPrivate::slotSetSystemLocale(void)
{
    setSystemLocale();
}

void
JveLocalizationPrivate::slotSetLocale(const QString &locale)
{
    loadTranslationsByLocale(locale);
}


