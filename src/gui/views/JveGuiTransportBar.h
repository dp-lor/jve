

#ifndef JVEGUITRANSPORTBAR_H
#define JVEGUITRANSPORTBAR_H


#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>


#include "../elements/JveGuiToolButton.h"
#include "../elements/JveGuiToolSpacer.h"
#include "../elements/JveGuiTimeFramesSpinsGroup.h"


class QEvent;


class JveGuiTransportBar : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiTransportBar(QWidget *parent);
        virtual  ~JveGuiTransportBar(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private slots:
        void slotSetState(const int state);
        void slotResetView(void);
        void slotSetPlayheadPosition(const int position);
    private:
        // members
        QHBoxLayout                mp_layout;
        JveGuiToolButton           mp_buttonSeekToStart;
        JveGuiToolButton           mp_buttonSeekToPrevKF;
        JveGuiToolButton           mp_buttonPlayPause;
        JveGuiToolButton           mp_buttonSeekToNextKF;
        JveGuiToolButton           mp_buttonSeekToEnd;
        JveGuiToolButton           mp_buttonLoop;
        JveGuiToolSpacer           mp_spacer;
        JveGuiTimeFramesSpinsGroup mp_playheadPositionSpinsGroup;
};


#endif // JVEGUITRANSPORTBAR_H


