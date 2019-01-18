

#ifndef JVEGUIPROJECTTREEVIEW_H
#define JVEGUIPROJECTTREEVIEW_H


#include <QWidget>
#include <QVBoxLayout>


#include "JveGuiTransportBar.h"
#include "JveGuiProjectTreeViewArea.h"


class JveGuiProjectTreeView : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectTreeView(QWidget *parent);
        virtual  ~JveGuiProjectTreeView(void);
    private:
        void restoreSettings(void);
        void saveSettings(void);
    private slots:
        void slotSetTransportBarPosition(const bool position);
    private:
        // members
        bool                      mp_transportBarPosition;
        QVBoxLayout               mp_layout;
        JveGuiTransportBar        mp_transportBar;
        JveGuiProjectTreeViewArea mp_area;
};


#endif // JVEGUIPROJECTTREEVIEW_H


