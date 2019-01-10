

#ifndef JVEGUIDOCKABLEWINDOW_H
#define JVEGUIDOCKABLEWINDOW_H


#include <QWidget>
#include <QString>
#include <QVBoxLayout>


class QShowEvent;
class QHideEvent;
class QCloseEvent;
class QAction;


class jveGuiDockableWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit jveGuiDockableWindow(
                  QWidget *parent,
            const QString &geometrySettingsKey,
            const QString &stateSettingsKey,
            const QString &extraSettingsKey
        );
        virtual ~jveGuiDockableWindow(void);
    protected:
        void showEvent(QShowEvent *event);
        void hideEvent(QHideEvent *event);
        void closeEvent(QCloseEvent *event);
    public:
        QAction * toggleAction(void);
        bool      isVisibleFromSettings(void) const;
    public:
        void fixVisibilityState(const bool isDockVisible);
        void setForcedClosing(const bool state);
    public:
        void attachView(QWidget *view);
        void detachView(QWidget *view);
    public:
        void restoreSettings(void);
        void saveSettings(void);
    signals:
        void closedWithoutToggler(void);
    protected:
        void       restoreState(const QByteArray &state);
        QByteArray saveState(void) const;
        void       restoreExtra(const QByteArray &data);
        QByteArray saveExtra(void) const;
    protected:
        // members
        bool        mp_forcedClosing;
        bool        mp_isVisibleFromSettings;
        QString     mp_geometrySettingsKey;
        QString     mp_stateSettingsKey;
        QString     mp_extraSettingsKey;
        QAction    *mp_toggleAction;
        QVBoxLayout mp_layout;
};


#endif // JVEGUIDOCKABLEWINDOW_H


