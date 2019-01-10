

#ifndef JVEGUIPROJECTTREEVIEW_H
#define JVEGUIPROJECTTREEVIEW_H


#include <QWidget>
#include <QVBoxLayout>


#include "jveGuiTransportBar.h"
#include "jveGuiProjectTreeViewArea.h"


class jveGuiProjectTreeView : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectTreeView(QWidget *parent);
        virtual  ~jveGuiProjectTreeView(void);
    private:
        void restoreSettings(void);
        void saveSettings(void);
    private slots:
        void slotSetTransportBarPosition(const bool position);
    private:
        // members
        bool                      mp_transportBarPosition;
        QVBoxLayout               mp_layout;
        jveGuiTransportBar        mp_transportBar;
        jveGuiProjectTreeViewArea mp_area;
};


#endif // JVEGUIPROJECTTREEVIEW_H


