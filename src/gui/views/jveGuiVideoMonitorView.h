

#ifndef JVEGUIVIDEOMONITORVIEW_H
#define JVEGUIVIDEOMONITORVIEW_H


#include <QWidget>
#include <QVBoxLayout>


#include "jveGuiVideoMonitorViewport.h"
#include "jveGuiVideoMonitorViewBar.h"


class jveGuiVideoMonitorView : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiVideoMonitorView(QWidget *parent);
        virtual  ~jveGuiVideoMonitorView(void);
    private slots:
        void slotSetState(const int state);
    private:
        // members
        int                        mp_state;
        QVBoxLayout                mp_layout;
        jveGuiVideoMonitorViewport mp_viewport;
        jveGuiVideoMonitorViewBar  mp_bar;
};


#endif // JVEGUIVIDEOMONITORVIEW_H


