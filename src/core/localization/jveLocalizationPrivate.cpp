

#include "jveLocalizationPrivate.h"


#include <QLocale>
#include <QLibraryInfo>
#include <QCoreApplication>


#include "../definitions/jveLocalizationDefines.h"
#include "../definitions/jveLocalizationMode.h"

#include "../mutexes/jveLocalizationMutex.h"
#include "../application/jveSettings.h"
#include "../signals/jveGlobalSignals.h"

#include "jveTr.h"


jveLocalizationPrivate jveLocalization;


jveLocalizationPrivate::jveLocalizationPrivate(void)
    : QObject(Q_NULLPTR),
        mp_mode(jveLocalizationMode::None),
        mp_locale(JVE_LOCALIZATION_FALLBACK_LOCALE),
        mp_qtTranslator(this),
        mp_coreTranslator(this),
        mp_guiTranslator(this)
{
}

jveLocalizationPrivate::~jveLocalizationPrivate(void)
{
}

void
jveLocalizationPrivate::initForCli(void)
{
    mp_mode |= jveLocalizationMode::Cli;

    setSystemLocale();
}

void
jveLocalizationPrivate::initForGui(void)
{
    mp_mode |= jveLocalizationMode::Gui;

    setLocaleFromSettings();
    wakeUp();
}

void
jveLocalizationPrivate::emitLocaleChangedSignal(void)
{
    emit jveGlobalSignals.localeChanged(mp_locale);
}

void
jveLocalizationPrivate::saveSettings(void)
{
    jveSettings.lock();

    jveLocalizationMutex.lock();

    jveSettings.setValue(
        JVE_SETTINGS_LOCALIZATION_LOCALE,
        mp_locale
    );

    jveLocalizationMutex.unlock();

    jveSettings.sync();
    jveSettings.unlock();
}

void
jveLocalizationPrivate::setSystemLocale(void)
{
    loadTranslationsByLocale(QLocale::system().name());
}

void
jveLocalizationPrivate::setLocaleFromSettings(void)
{
    jveSettings.lock();

    QString locale = jveSettings.contains(JVE_SETTINGS_LOCALIZATION_LOCALE)
        ? jveSettings.value(JVE_SETTINGS_LOCALIZATION_LOCALE).toString()
        : QLocale::system().name();

    loadTranslationsByLocale(locale);

    jveSettings.unlock();
}

void
jveLocalizationPrivate::wakeUp(void)
{
    // slot set system locale
    connect(
        &jveGlobalSignals,
        SIGNAL(wantSetSystemLocale()),
        this,
        SLOT(slotSetSystemLocale()),
        Qt::QueuedConnection
    );
    // slot set locale
    connect(
        &jveGlobalSignals,
        SIGNAL(wantSetLocale(QString)),
        this,
        SLOT(slotSetLocale(QString)),
        Qt::QueuedConnection
    );
}

void
jveLocalizationPrivate::loadTranslationsByLocale(const QString &locale)
{
    jveLocalizationMutex.lock();

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
    if (mp_mode & jveLocalizationMode::Gui) {
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
    jveTr.update();

    emitLocaleChangedSignal();

    jveLocalizationMutex.unlock();
}

void
jveLocalizationPrivate::slotSetSystemLocale(void)
{
    setSystemLocale();
}

void
jveLocalizationPrivate::slotSetLocale(const QString &locale)
{
    loadTranslationsByLocale(locale);
}


