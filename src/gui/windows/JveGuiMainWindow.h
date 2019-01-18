

#ifndef JVEGUIMAINWINDOW_H
#define JVEGUIMAINWINDOW_H


#include <QMainWindow>
#include <QList>
#include <QString>
#include <QStatusBar>


#include "../menus/JveGuiMenuFile.h"
#include "../menus/JveGuiMenuEdit.h"
#include "../menus/JveGuiMenuView.h"
#include "../menus/JveGuiMenuWindow.h"
#include "../menus/JveGuiMenuHelp.h"
#include "../menus/JveGuiMenuLanguage.h"

#include "../docks/JveGuiProjectTreeDock.h"
#include "../docks/JveGuiProjectSettingsDock.h"
#include "../docks/JveGuiVideoMonitorDock.h"
#include "../docks/JveGuiProjectSourcesDock.h"
#include "../docks/JveGuiHistoryDock.h"


class QEvent;
class QCloseEvent;
class QKeyEvent;


class JveGuiMainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit  JveGuiMainWindow(void);
        virtual  ~JveGuiMainWindow(void);
    protected:
        void changeEvent(QEvent *event);
        void closeEvent(QCloseEvent *event);
        void keyPressEvent(QKeyEvent *event);
    public:
        QList<JveGuiWindowableDock *> & windowableDocks(void);
    public:
        void restoreSettings(void);
        void saveSettings(void);
    public:
        void clearStatusBarMessage(void);
        void showStatusBarMessage(const QString &message);
    private slots:
        void slotStateChanged(const int state);
        void slotRejectExitSignalSent(void);
        void slotSetWindowTitle(const QString &title);
        void slotToggleStatusBar(const bool enabled);
        void slotToggleFullScreen(const bool enabled);
    private:
        // members
        bool mp_wantExitSignalSent;
        bool mp_maximizedBeforeFullScreen;
        // menu
        JveGuiMenuFile     mp_menuFile;
        JveGuiMenuEdit     mp_menuEdit;
        JveGuiMenuView     mp_menuView;
        JveGuiMenuWindow   mp_menuWindow;
        JveGuiMenuHelp     mp_menuHelp;
        JveGuiMenuLanguage mp_menuLanguage;
        // status bar
        QStatusBar mp_statusBar;
        // windowable docks
        QList<JveGuiWindowableDock *> mp_windowableDocks;
        // docks
        JveGuiProjectTreeDock     mp_projectTreeDock;
        JveGuiProjectSettingsDock mp_projectSettingsDock;
        JveGuiVideoMonitorDock    mp_videoMonitorDock;
        JveGuiProjectSourcesDock  mp_projectSourcesDock;
        JveGuiHistoryDock         mp_historyDock;
};


#endif // JVEGUIMAINWINDOW_H


