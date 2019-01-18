

#ifndef JVEGLOBALSIGNALSPRIVATE_H
#define JVEGLOBALSIGNALSPRIVATE_H


#include <QObject>
#include <QString>


#include "../application/jveReport.h"


class jveGlobalSignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  jveGlobalSignalsPrivate(void);
        virtual  ~jveGlobalSignalsPrivate(void);
    signals:

        // report
        void wantShowReport(const jveReport &report);

        // exit/quit
        void wantExit(void);
        void wantRejectQuit(void);
        void wantAcceptQuit(void);

        // states
        void stateChanged(const int state);
        void guiStateChanged(const int state);

        // application watchers
        void wantSendUiChangeEventType(const int eventType);

        // edit menu
        void wantCut(void);
        void wantCopy(void);
        void wantPaste(void);
        void wantRemove(void);
        void wantShowPreferencesDialog(void);

        // view menu
        void wantSetUpTransportBarFeatures(const bool position);
        void wantSetTransportBarPosition(const bool position);
        void wantSetUpRulerFeatures(const bool checked, const int type);
        void wantToggleRuler(const bool status);
        void wantSetRulerType(const int type);
        void wantSetUpStatusBarToggler(const bool checked);
        void wantToggleStatusBar(const bool status);
        void wantSetUpFullScreenToggler(const bool checked);
        void wantToggleFullScreen(const bool status);

        // help menu
        void wantShowKeyboardShortcutsInfo(void);
        void wantShowAboutJveDialog(void);

        // language menu
        void localeChanged(const QString &locale);
        void wantSetSystemLocale(void);
        void wantSetLocale(const QString &locale);

};


#endif // JVEGLOBALSIGNALSPRIVATE_H


