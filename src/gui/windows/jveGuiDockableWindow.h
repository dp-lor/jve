

#ifndef JVEGUIDOCKABLEWINDOW_H
#define JVEGUIDOCKABLEWINDOW_H


#include <QWidget>
#include <QString>
#include <QByteArray>
#include <QVBoxLayout>


#include "../elements/jveGuiAction.h"


class QCloseEvent;


class jveGuiDockableWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit jveGuiDockableWindow(
                  QWidget *parent,
            const QString &visibleSettingsKey,
            const QString &geometrySettingsKey,
            const QString &extraSettingsKey
        );
        virtual ~jveGuiDockableWindow(void);
    protected:
        void closeEvent(QCloseEvent *event);
    signals:
        void closedWithoutToggler(void);
    public:
        QAction * toggleAction(void);
    public:
        bool isVisibleBySettings(void) const;
    public:
        void fixVisibleBySettings(const bool isDockVisible);
        void setForcedClosing(const bool forced);
    public:
        void show(void);
        void hide(void);
        void attachView(QWidget *view);
        void detachView(QWidget *view);
    protected:
        void readAllSettings(void);
        void restoreVisibleState(void);
    protected:
        void updateSettingsForShow(void);
        void updateSettingsForHide(const bool forcedClosing = false);
        void saveAllSettings(void);
    protected:
        // forced close flag
        bool mp_closeForced;
        // settings keys
        QString mp_visibleSettingsKey;
        QString mp_geometrySettingsKey;
        QString mp_extraSettingsKey;
        // settings
        bool             mp_visible;
        QByteArray       mp_geometry;
        Qt::WindowStates mp_state;
        // members
        jveGuiAction *mp_toggleAction;
        QVBoxLayout   mp_layout;
};


#endif // JVEGUIDOCKABLEWINDOW_H


