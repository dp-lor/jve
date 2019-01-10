

#ifndef JVEGUIMAINWINDOW_H
#define JVEGUIMAINWINDOW_H


#include <QMainWindow>
#include <QEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QString>
#include <QMenuBar>
#include <QStatusBar>


#include "../menus/jveGuiMenuFile.h"
#include "../menus/jveGuiMenuEdit.h"
#include "../menus/jveGuiMenuView.h"
#include "../menus/jveGuiMenuWindow.h"
#include "../menus/jveGuiMenuHelp.h"
#include "../menus/jveGuiMenuLanguage.h"

#include "../docks/jveGuiProjectTreeDock.h"
#include "../docks/jveGuiProjectSettingsDock.h"
#include "../docks/jveGuiVideoMonitorDock.h"
#include "../docks/jveGuiProjectSourcesDock.h"
#include "../docks/jveGuiHistoryDock.h"


class jveGuiMainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit  jveGuiMainWindow(void);
        virtual  ~jveGuiMainWindow(void);
    protected:
        void changeEvent(QEvent *event);
        void closeEvent(QCloseEvent *event);
        void keyPressEvent(QKeyEvent *event);
    public:
        QList<jveGuiWindowableDock *> & windowableDocks(void);
    public:
        void restoreSettings(void);
        void saveSettings(void);
        void clearStatusBarMessage(void);
        void showStatusBarMessage(const QString &message);
    private slots:
        void slotRejectExitSignalSent(void);
        void slotStateChanged(const int state);
        void slotSetWindowTitle(const QString &title);
        void slotToggleStatusBar(const bool enabled);
        void slotToggleFullScreen(const bool enabled);
    private:
        // members
        bool                           mp_wantExitSignalSent;
        bool                           mp_isMaximizedBeforeFullScreen;
        QMenuBar                      *mp_menuBar;
        jveGuiMenuFile                 mp_menuFile;
        jveGuiMenuEdit                 mp_menuEdit;
        jveGuiMenuView                 mp_menuView;
        jveGuiMenuWindow               mp_menuWindow;
        jveGuiMenuHelp                 mp_menuHelp;
        jveGuiMenuLanguage             mp_menuLanguage;
        QStatusBar                     mp_statusBar;
        QList<jveGuiWindowableDock *>  mp_windowableDocks;
        jveGuiProjectTreeDock          mp_projectTreeDock;
        jveGuiProjectSettingsDock      mp_projectSettingsDock;
        jveGuiVideoMonitorDock         mp_videoMonitorDock;
        jveGuiProjectSourcesDock       mp_projectSourcesDock;
        jveGuiHistoryDock              mp_historyDock;
};


#endif // JVEGUIMAINWINDOW_H


