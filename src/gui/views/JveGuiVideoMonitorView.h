

#ifndef JVEGUIVIDEOMONITORVIEW_H
#define JVEGUIVIDEOMONITORVIEW_H


#include <QWidget>
#include <QVBoxLayout>


#include "JveGuiVideoMonitorViewport.h"
#include "JveGuiVideoMonitorViewBar.h"


class JveGuiVideoMonitorView : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiVideoMonitorView(QWidget *parent);
        virtual  ~JveGuiVideoMonitorView(void);
    private slots:
        void slotSetState(const int state);
    private:
        // members
        int                        mp_state;
        QVBoxLayout                mp_layout;
        JveGuiVideoMonitorViewport mp_viewport;
        JveGuiVideoMonitorViewBar  mp_bar;
};


#endif // JVEGUIVIDEOMONITORVIEW_H


