

#ifndef JVELOCALIZATIONPRIVATE_H
#define JVELOCALIZATIONPRIVATE_H


#include <QObject>
#include <QString>
#include <QTranslator>


class jveLocalizationPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  jveLocalizationPrivate(void);
        virtual  ~jveLocalizationPrivate(void);
    public:
        void initForCli(void);
        void initForGui(void);
        void emitLocaleChangedSignal(void);
    public:
        void saveSettings(void);
    private:
        void setSystemLocale(void);
        void setLocaleFromSettings(void);
        void wakeUp(void);
        void loadTranslationsByLocale(const QString &locale);
    private slots:
        void slotSetSystemLocale(void);
        void slotSetLocale(const QString &locale);
    private:
        // members
        int         mp_mode;
        QString     mp_locale;
        QTranslator mp_qtTranslator;
        QTranslator mp_coreTranslator;
        QTranslator mp_guiTranslator;
};


#endif // JVELOCALIZATIONPRIVATE_H


